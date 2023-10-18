#ifndef DLLIST_H
#define DLLIST_H

#include <stdexcept>
#include <iostream>

template<typename Type>

class DLList
{

//Nested struct node
private: struct Node{

        Type m_data; //Guarda el tipo de dato

        Node *m_previous; //Referencia al siguiente nodo
        Node *m_next; //Referencia al nodo anterior

        //Constructor por copia
        //Los punteros y datos se inician como nulos
        Node(const Type &data = Type{}, Node *next = nullptr, Node *previous = nullptr)
        : m_data{data}, m_next{next}, m_previous{previous} {}

        //Constructor por referencia
        //Los punteros se inician como nulos
        Node(Type &&data, Node *next = nullptr, Node *previous = nullptr) :
        m_data{data}, m_next{next}, m_previous{previous} {}
    };


//Nested class iterator
public: class iterator{

    public:

        //Constructor implícito
        //Inicia su puntero como nulo
        iterator() : m_current{nullptr}{}

        //Destructor se emplea el defecto
        ~iterator() = default;

        //Operador * 
        //Permite el regreso de valor como puntero
        Type &operator*() {
            if(m_current == nullptr){
                throw std::logic_error("Trying to dereference a null pointer.");
            }
            else{
                return m_current->m_data;
            }

        }

        //Operador ++
        //Se avanza al siguiente nodo de la lista siempre y cuando no sea el ultimo nodo
        iterator operator++(){
            if(m_current){
                m_current = m_current->m_next;
            }
            else{
                throw std::logic_error("Trying to increment past end.");
            }

            return *this;
        }

        //Operador ++
        //Mantiene cuenta de la posición en la que se esta
        iterator operator++(int){
            iterator old = *this;
            ++(*this);
            return old;
        }

        //Operador --
        //Regresa al nodo anterior
        iterator operator--(){
            if(m_current){
                m_current = m_current->m_previous;
            }
            else{
                throw std::logic_error("Trying to decrement past beginning");
            }
            return *this;
        }

        //Operador --
        //Mantiene cuenta de la posición en la que se esta
        iterator operator--(int){
            iterator old = *this;
            --(*this);
            return old;
        }

        iterator &operator+( int addition){
           for(int i = 0; i<addition; i++){
            ++(*this);
           }
            return *this;
        }

        //Operador ==
        //indica si el ambos iteradores apuntan a la misma dirección de memoria
        bool operator==(const iterator &rhs) { return  m_current == rhs.m_current; }

        //Operador !=
        //indica si el ambos iteradores apuntan a distinta dirección de memoria
        bool operator!=(const iterator &rhs) {return m_current != rhs.m_current;}

    private:
        //Puntero al nodo actual
        Node *m_current;

        //Constructor con parámetro
        //Recibe el puntero de un nodo al cual iguala su propio puntero
        iterator(Node *current) : m_current{current}{}

        //La clase DDList puede acceder a los miembro privados
        friend class DLList<Type>;
    
    };


public:

    //Constructor implícito
    //Inicializa la lista
    DLList() { init(); }

    //Destructor
    //Vacía la lista y elimina los nodos cabeza y cola
    ~DLList(){
        clear();
        delete m_head;
        delete m_tail;
    }

    //Insertar con iterador
    //Recibe un iterador y un objeto
    //Inserta el objeto en la posición del iterador
    iterator insert(iterator position, const Type &object) {
       Node *p_current = position.m_current;
       m_size++;
       return {p_current->m_previous = p_current->m_previous->m_next = new Node{object,p_current,p_current->m_previous}};
    }

    //Insertar con posición 
    //Recibe un entero y un objeto
    //En la posición indicada se genera un iterador y se inserta el objeto 
    void insert(int position, const Type &object){
        insert(generateIterator(position),object);
    }

    //Insertar por referencia
    //Recibe un iterador y una referencia
    iterator insert(iterator position, Type &&object) {
      Node *p_current = position.m_current;
       m_size++;
       return {p_current->m_previous = p_current->m_previous->m_next = new Node{std::move(object),p_current,p_current->m_previous}};
    }

    //Insertar por referencia
    //Recibe un entero y una referencia
    void insert(int position, const Type &&object){
        insert(generateIterator(position),object);
    }

    //Generar iterador
    //Genera un iterador a partir de un entero
    //EWl iterador se encuentra en la posición indicada por el entero
    iterator generateIterator(int position){
        
        if(position<0 || position>m_size+1){
            throw std::logic_error("Trying to generate an out of bounds iterator");
        }
        else{
            iterator posIter = begin();
            for(int i = 0; i != position; i++){
                posIter++;
            }

        return  posIter;   
        }
        
    }


    //Agregar al final por copia
    //Agrega un elemento al final de la lista
    void push_back(const Type &object){
        insert(end(),object);
    }

    //Agregar al final por referencia
    //Agrega un elemento al final de la lista
    void push_back(Type &&object){
       insert(end(),std::move(object));
    }

    //Agregar al inicio
    //Agrega un elemento al inicio de la lista
    void push_front(const Type &object){
        insert(begin(),object);
    }

     //Agregar al inicio por referencia
    //Agrega un elemento al inicio de la lista
    void push_front(Type &&object){
       insert(begin(),std::move(object));
    }

    //Eliminar al inicio
    //Elimina el primer elemento de la lista
    void pop_front(){
        if(IsEmpty()){
            throw std::logic_error("List is empty");
        }
        else{
          erase(begin());
        }
    }

    //Borrar
    //Borra el elemento encontrado en la posición indicada por el iterador
    iterator erase(iterator itr){

        if(itr == end()){
            throw std::logic_error("Cannot erase at end iterator");
        }
        Node *position = m_head;
        while (position->m_next != itr.m_current){
            position = position->m_next;
        }
        position->m_next = itr.m_current->m_next;
        delete itr.m_current;
        m_size--;
        return iterator(m_head->m_next);
        
    }

    //Borrar
    //Borra el elemento en la posición indicada
    void erase(int position){
        erase(generateIterator(position));
    }

    //Limpiar
    //Elimina todos los elementos de la lista
    void clear(){
        while (!IsEmpty()){
            pop_front();
        }
    }

    //Imprimir
    //Imprime todos los elementos de la lista
    void print(){
        iterator itr = begin();
        while (itr != end()){
            std::cout << *itr << " ";
            itr++;
        }
        std::cout << std::endl;
    }

    //Getters

    //Regresa el inicio de la lista
    iterator begin() { return m_head->m_next; }

    //Regresa el final de la lista
    iterator end() { return m_tail; }

    //Regresa el tamaño de la lista
    int size() { return m_size;}

    //Regresa si la lista esta o no vacía
    bool IsEmpty() const { return m_size == 0; }

private:

    Node *m_head; //Nodo inicial
    Node *m_tail; //Nodo final

    int m_size; //Tamaño de la lista

    //Inicializar
    //Crea el nodo inicial y final
    //Apunta el siguiente nodo del inicial al final y el anterior a nulo
    //Apunta el anterior nodo del final al inicial y el siguiente a nulo
    void init(){
        m_head = new Node();
        m_tail = new Node();
        m_size = 0;

        m_head->m_next = m_tail;
        m_head->m_previous = nullptr;

        m_tail->m_next = nullptr;
        m_tail->m_previous = m_head;
    }
};

#endif