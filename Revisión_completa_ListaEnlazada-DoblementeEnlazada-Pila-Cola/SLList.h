#ifndef SLLLIST_H
#define SLLLIST_H

#include <iostream>
#include <utility>


template <typename Object> //Nombre de la plantilla, para asi poder recibir distintos tipos de datos
class SLList {
private:
   
   //Estructura anidada privada nodo
    struct Node  {

        Object data; //Guarda la información del tipo correspondiente
        Node *next; //Puntero al siguiente nodo de la lista

        //Constructor por defecto y por copia -- Implicito
        //Si se proporciona un objeto y su puntero estos serán guardados en data y next
        //Si no se proporciona, se guardara un objeto vació en data y un puntero nulo en next
        Node(const Object &d = Object{}, Node *n = nullptr)
            : data{d}, next{n} {}

        //Constructor de referencia
        //Recibe un nodo como parámetro, con el cual cambia sus parámetros data y next
        Node(Object &&d, Node *n = nullptr)
            : data{std::move(d)}, next{n} {}
    };

public:
    //Clase anidada publica iterador
    class iterator {
    public:

        iterator() : current{nullptr} {} //Constructor por defecto. Implicito  Inicia su valor puntero como nulo

        //Operador puntero
        //Si el puntero es nulo regresa un error
        //Si contiene algo regresa el objeto al que apunta su puntero
        Object &operator*() {
            if(current == nullptr)
                throw std::logic_error("Trying to dereference a null pointer.");
            return current->data;
        }

        //Operador de incremento 
        //Si existe un siguiente nodo, cambia su puntero actual a dicho nodo y lo regresa
        //Si no existe un siguiente nodo arroja un error lógico
        //Se encarga de mover el apuntador de la memoria
        iterator &operator++() {
            if(current){
                current = current->next;
            }    
            else
                throw std::logic_error("Trying to increment past the end.");
            return *this;
        }

        //Operador de incremento 
        //Lleva el conteor del nodo en el que se encutra 
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        //Operador de igualdad
        //Si ambos iteradores tienen el mismo apuntador al nodo se regresa verdadero, de lo contrario falso
        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }

        //Operador de desigualdad
        //Si ambos iteradores tienen el distinto apuntador al nodo se regresa verdadero, de lo contrario falso
        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }

    private:
        Node *current; //Guarda un puntero al nodo actual
        iterator(Node *p) : current{p} {} //Constructor con parámetro. Recibe un nodo como parámetro al cual apunta su apuntador
        
        friend class SLList<Object>; //La plantilla SLList<Object> puede acceder también los mismbros privados y prodejidos 
    };

public:

    //Constructor implicito
    /*
    Crea una lista vacía de tamaño 0
    Crea un nodo cabeza y uno cola
    Apunta el siguiente nodo de la cabeza al nodo cola
    */
    SLList() : head(new Node()), tail(new Node()), theSize(0) {
        head->next = tail;
    }

    //Destructor
    //Vacía la lista con el método clear
    //Después borre el nodo cabeza y cola
    ~SLList() {
        clear();
        delete head;
        delete tail;
    }


    iterator begin() { return {head->next}; } //Inicio regresa el siguiente nodo a la cabeza
    iterator end() { return {tail}; } //Final regresa el nodo cola

    //Tamaño
    //Regresa el tamaño de la lista.
    int size() const { return theSize; }

    //Vació
    //Comprueba si la lista contiene o no algún elemento.
    bool empty() const { return size() == 0; }

    void clear() { while (!empty()) pop_front(); }

    //Frente
    //Si la lista no esta vacía regresa el primer elemento.
    Object &front() {
        if(empty()){
            throw std::logic_error("List is empty.");
        } 
        return *begin();
    }


    //Insertar al frente copia
    //Inserta un nodo en la posición frontal usando la función para insertar y un iterador que apunta al frente con el método begin
    void push_front(const Object &x) { insert(begin(), x); }

    //Insertar al frente referencia
    //Inserta un nodo en la posición frontal usando la función para insertar y un iterador que apunta al frente con el método begin
    void push_front(Object &&x) { insert(begin(), std::move(x)); }

    //Eliminar frente
    //Elimina el elemento de la lista usando la función de borrar y un iterador que apunta al frente con el método begin
    //Si la lista esta vacía da un error lógico, ya que no hay nada que borrar
    void pop_front() {
        if(empty())
            throw std::logic_error("List is empty.");
        erase(begin());
    }

    //Insertar por referencia
    /*
    Creamos un puntero al nodo el cual apunta al iterador
    Hacemos que el apuntador siguiente de la cabeza se iguale a un nuevo nodo, el cual tiene una copia del objeto pasado por parámetro, y el siguiente puntero de head como current
    Incrementamos el tamaño de la lista en 1
    Regresamos el el apuntador al nuevo nodo
    */
    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.current;
        head->next = new Node{x, head->next};
        theSize++;
        return iterator(head->next);
    }

    //Insertar por copia
    /*
    Creamos un puntero al nodo el cual apunta al iterador
    Hacemos que el apuntador siguiente de la cabeza sea a un nuevo nodo, el cual mueve el contenido del objeto pasado por parámetro, y el siguiente puntero de head como current
    Incrementamos el tamaño de la lista en 1
    Regresamos el el apuntador al nuevo nodo
    */
    iterator insert(iterator itr, Object &&x) {
        Node *p = itr.current;
        head->next = new Node{std::move(x), head->next};
        theSize++;
        return iterator(head->next);
    }

    //Borrar
    /*
    Si se intenta borrar el iterador cola se da un error lógico
    Se crea un puntero a un nodo, el cual se desplazara hasta estar en la misma posición del del iterador pasado por parámetro
    Se elimina el elemento al que apunta el iterador
    Reducimos el tamaño de la lista en uno
    Y regresamos el iterador copia para guardarlo en el nodo anterior y mantener la continuidad de la lista
    */
    iterator erase(iterator itr) {
        if (itr == end()){
            throw std::logic_error("Cannot erase at end iterator");
        }    
        Node *p = head;

        while (p->next != itr.current) { p = p->next; }

        p->next = itr.current->next;
        delete itr.current;
        theSize--;
        return iterator(p->next);
    }

    //Imprimir lista
    //Imprime todos los elementos de la lista con ayuda de un iterador 
    void printList() {
        iterator itr = begin();
        while (itr != end()) {
            std::cout << *itr << " ";
            ++itr;
        }
        std::cout << std::endl;
    }

private:
    //Miembros privados
    Node *head; //Apuntador al inicio de la lista
    Node *tail; //Apuntador al final de la lista
    int theSize;//Tamaño de la lista
    
    //Inicializado de la lista
    void init() {
        theSize = 0; //Tamaño por defecto
        head->next = tail; //Si la lista esta vacía el siguiente elemento del inicio es el final
    }
};

#endif
