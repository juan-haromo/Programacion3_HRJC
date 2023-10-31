#ifndef QUEUE.H
#define QUEUE.H

template <typename Type>
class Queue : private DLList<Type>
{

public:

    //Constructor explicito
    Queue(){
        DLList<Type>::init();
    }

    //Destructor 
    ~Queue(){
        clear();//Limpiamos la queue
        //Eliminamos los nodos centinelas
        delete DLList<Type>::m_head;
        delete DLList<Type>::m_tail;
    }

    //Enfilar
    //Agrega un elemento al final de la fila copia
    void enqueue(Type &data){
        DLList<Type>::push_back(data); //Usamos la funcion pop back de DLList que agrega un dato al final 
    }

    //Enfilar
    //Agrega un elemento al final de la fila referencia
    void enqueue(Type &&data){
        DLList<Type>::push_back(std::move(data));  //Usamos la funcion pop back de DLList que agrega un dato al final 
    }

    //Des-enfilar
    //Sacamos el primer elemento de la fila
    void dequeue(){
        DLList<Type>::pop_front(); //Usamos la funcion pop_front de la DLList que elimina el primer elemento de la lista
    }

    //Imprimir
    //Imprimimos la queue
    void print(){
        DLList<Type>::print(); //Usamos la funcion de imprimir de la DLList
    }

    //Front
    //Regresamos el primer elemento de la lista
    Type front(){
        return DLList<Type>::m_head->m_next->m_data;
    }

    //Limpiar
    //Limpiamos la lista
    void clear(){
        DLList<Type>::clear(); //Borramos todos los elemntos de la lista usando la funcion clear de DLList
    }
};

#endif
