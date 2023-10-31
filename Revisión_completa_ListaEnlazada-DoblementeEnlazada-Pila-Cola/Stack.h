#ifndef STACK.H
#define STACK.H 

template<typename Type>
class Stack : private DLList<Type>
{
private:
    
public:

    //Constructor explicito
    Stack(){
       DLList<Type>::init();
    }
    
    //Destructor
    ~Stack(){
        clear(); //Limpiamos la lista
        //Eliminamos ambos nodos centinelas
        delete DLList<Type>::m_head; 
        delete DLList<Type>::m_tail;
    }

    //Agregar un elemento por referencia
    void push(Type &data){
        DLList<Type>::push_back(data); //Usamos la funcion push back que agrega un elemento al final
    }

    //Agregar un elemento por copia
    void push(Type &&data){
        DLList<Type>::push_back(std::move(data)); //Usamos la funcion push back que agrega un elemento al final
    }

    //Imprimir
    void print(){
        DLList<Type>::print(); //Imprimimos usando el metodo imprimir de la DLList
    }

    //Pop
    void pop(){
       DLList<Type>::pop_back(); //Eliminamos el ultimo elemento del stack usando el pop bka c de la DLList
    }

    //Limpiar
    void clear(){
        DLList<Type>::clear();//Limpiamos el stack usando la funcion limpiar de la DLList
    }

    Type top(){
        return DLList<Type>::m_tail->m_previous->m_data; //Regresamos la informacion del elemento que se encuentra en el top del stack
    }

};

#endif