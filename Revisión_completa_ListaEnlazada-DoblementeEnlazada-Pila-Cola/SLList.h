#ifndef SLLLIST_H
#define SLLLIST_H

#include <iostream>
#include <utility>


template <typename Type> //Nombre de la plantilla, para asi poder recibir distintos tipos de datos
class SLList {
private:
   //Estructura anidada privada nodo
    struct Node  {

        Type m_data; //Guarda la información del tipo correspondiente
        Node *m_next; //Puntero al siguiente nodo de la lista

        //Constructor por defecto y por copia -- Implicito
        //Si se proporciona un objeto y su puntero estos serán guardados en m_data y m_next
        //Si no se proporciona, se guardara un objeto vació en m_data y un puntero nulo en m_next
        Node(const Type &data = Type{}, Node *next = nullptr)
            : m_data{data}, m_next{next} {}

        //Constructor de referencia
        //Recibe un nodo como parámetro, con el cual cambia sus parámetros m_data y m_next
        Node(Type &&data, Node *next = nullptr)
            : m_data{std::move(data)}, m_next{next} {}
    };

public:
    //Clase anidada publica iterador
    class iterator {
    public:

        iterator() : m_current{nullptr} {} //Constructor por defecto. Implicito  Inicia su valor puntero como nulo

        //Operador puntero
        //Si el puntero es nulo regresa un error
        //Si contiene algo regresa el objeto al que apunta su puntero
        Type &operator*() {
            if(m_current == nullptr)
                throw std::logic_error("Trying to dereference a null pointer.");
            return m_current->m_data;
        }

        //Operador de incremento 
        //Si existe un siguiente nodo, cambia su puntero actual a dicho nodo y lo regresa
        //Si no existe un siguiente nodo arroja un error lógico
        //Se encarga de mover el apuntador de la memoria
        iterator &operator++() {
            if(m_current){
                m_current = m_current->m_next;
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
            return m_current == rhs.m_current;
        }

        //Operador de desigualdad
        //Si ambos iteradores tienen el distinto apuntador al nodo se regresa verdadero, de lo contrario falso
        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }

    private:
        Node *m_current; //Guarda un puntero al nodo actual
        iterator(Node *current) : m_current{current} {} //Constructor con parámetro. Recibe un nodo como parámetro al cual apunta su apuntador
        
        friend class SLList<Type>; //La plantilla SLList<Type> puede acceder también los mismbros privados y prodejidos 
    };

public:

    //Constructor implicito
    /*
    Crea una lista vacía de tamaño 0
    Crea un nodo cabeza y uno cola
    Apunta el siguiente nodo de la cabeza al nodo cola
    */
    SLList() : m_head(new Node()), m_tail(new Node()), m_size(0) {
        m_head->m_next = m_tail;
    }

    //Destructor
    //Vacía la lista con el método clear
    //Después borre el nodo cabeza y cola
    ~SLList() {
        clear();
        delete m_head;
        delete m_tail;
    }


    iterator begin() { return {m_head->m_next}; } //Inicio regresa el siguiente nodo a la cabeza
    iterator end() { return {m_tail}; } //Final regresa el nodo cola

    //Tamaño
    //Regresa el tamaño de la lista.
    int size() const { return m_size; }

    //Vació
    //Comprueba si la lista contiene o no algún elemento.
    bool empty() const { return size() == 0; }

    void clear() { while (!empty()) pop_front(); }

    //Frente
    //Si la lista no esta vacía regresa el primer elemento.
    Type &front() {
        if(empty()){
            throw std::logic_error("List is empty.");
        } 
        return *begin();
    }


    //Insertar al frente copia
    //Inserta un nodo en la posición frontal usando la función para insertar y un iterador que apunta al frente con el método begin
    void push_front(const Type &data) { insert(begin(), data); }

    //Insertar al frente referencia
    //Inserta un nodo en la posición frontal usando la función para insertar y un iterador que apunta al frente con el método begin
    void push_front(Type &&data) { insert(begin(), std::move(data)); }

    //Eliminar frente
    //Elimina el elemento de la lista usando la función de borrar y un iterador que apunta al frente con el método begin
    //Si la lista esta vacía da un error lógico, ya que no hay nada que borrar
    void pop_front() {
        if(empty()){
            throw std::logic_error("List is empty.");
        }  
        erase(begin());
    }

    //Insertar por referencia
    /*
    Creamos un puntero al nodo el cual apunta al iterador
    Hacemos que el apuntador siguiente de la cabeza se iguale a un nuevo nodo, el cual tiene una copia del objeto pasado por parámetro, y el siguiente puntero de m_head como m_current
    Incrementamos el tamaño de la lista en 1
    Regresamos el el apuntador al nuevo nodo
    */
    iterator insert(iterator position, const Type &data) {
       Node *previous = begin();
       while(previous->m_next != position.m_current){ previous = previous->m_next;}
       m_size++;

       return (previous->m_next = new Node(data,position->m_current));
    }

    //Insertar por copia
    /*
    Creamos un puntero al nodo el cual apunta al iterador
    Hacemos que el apuntador siguiente de la cabeza sea a un nuevo nodo, el cual mueve el contenido del objeto pasado por parámetro, y el siguiente puntero de m_head como m_current
    Incrementamos el tamaño de la lista en 1
    Regresamos el el apuntador al nuevo nodo
    */
    iterator insert(iterator position, Type &&data) {
      Node *previous = m_head;
       while(previous->m_next != position.m_current){ previous = previous->m_next;}
        m_size++;

       return {previous->m_next = new Node{std::move(data),position.m_current}}; 
    }

    
    //Borrar
    /*
    Si se intenta borrar el iterador cola se da un error lógico
    Se crea un puntero a un nodo, el cual se desplazara hasta estar en la misma posición del del iterador pasado por parámetro
    Se elimina el elemento al que apunta el iterador
    Reducimos el tamaño de la lista en uno
    Y regresamos el iterador copia para guardarlo en el nodo anterior y mantener la continuidad de la lista
    */
    iterator erase(iterator position) {
        
        if (position == end()){
            throw std::logic_error("Cannot erase at end iterator");
        }    
        Node *current = m_head;
        while (current->m_next != position.m_current) { current = current->m_next; }
        current->m_next = position.m_current->m_next;
        delete position.m_current;
        m_size--;
        return iterator(current->m_next);
    }

    //Imprimir lista
    //Imprime todos los elementos de la lista con ayuda de un iterador 
    void print() {
        iterator position = begin();
        while (position != end()) {
            std::cout << *position << " ";
            ++position;
        }
        std::cout << std::endl;
    }

private:
    //Miembros privados
    Node *m_head; //Apuntador al inicio de la lista
    Node *m_tail; //Apuntador al final de la lista
    int m_size;//Tamaño de la lista
    
    //Inicializado de la lista
    void init() {
        m_size = 0; //Tamaño por defecto
        m_head->m_next = m_tail; //Si la lista esta vacía el siguiente elemento del inicio es el final
        m_tail->m_next = nullptr;
    }
};

#endif
