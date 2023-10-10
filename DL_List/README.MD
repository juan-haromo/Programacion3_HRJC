# Lista doblemente enlazada (*Double linked list* *DLList*) <br>

La lista doblemente anidada es una estructura de datos en la cual se cuenta con elementos vinculados tanto al siguiente elemento como al anterior.<br>

Para esta clase se requiere de una estructura y una clase anidada.<br>

## Nodo <br>

Los nodos son una estructura anidada, la cual nos ayuda a guardar el tipo de dato deseado, mediante el uso de una plantilla.<br>
``` c++ 
template<typename Type>
Type m_data; 
```

En estos también encontramos los punteros al miembro anterior y siguiente de la lista. <br>

```c++
Node *m_previous; 
Node *m_next;
```

Asi como su constructor por copia y referencia, los cuales reciben valores para los datos del nodo, de no recibirlos los igualan a nulo. <br>

```c++
//Copia
Node(const Type &data = Type{}, Node *next = nullptr, Node *previous = nullptr)
    : m_data{data}, m_next{next}, m_previous{previous} {}

//Referencia
Node(Type &&data, Node *next = nullptr, Node *previous = nullptr) 
    : m_data{data}, m_next{next}, m_previous{previous} {}
```

## Iterador <br>

Los iteradores son una clase anidada que encontramos en la *DLList*, estos tiene la función de recorrer la lista y mantener la posición en la que se encuentran. <br>

### Operador ++ <br>
Debido a que nos encontramos en una lista doblemente enlazada estos pueden avanzar hacia adelante en la lista mediante el operador ++.<br>
```c++
iterator operator++(){
    if(m_current){
        m_current = m_current->m_next;
    }
    else{
        throw std::logic_error("Trying to increment past end.");
    }
    return *this;
}
```

### Operador -- <br>
Pero, debido al doble enlace también pueden retroceder en los elementos de la lista mediante el operador --.<br>
```c++
iterator operator--(){
    if(m_current){
        m_current = m_current->m_previous;
    }
    else{
            throw std::logic_error("Trying to decrement past beginning");
    }
    return *this;
}
```
### Comparación
Pueden ser comparados mediante los operadores == y !=
```c++
bool operator==(const iterator &rhs) { return  m_current == rhs.m_current; }

bool operator!=(const iterator &rhs) {return m_current != rhs.m_current;}
```

Asi mismo tienen como clase amiga a la DLList para que esta puede usar sus funciones privadas  y protegidas. <br>

## *DLList*

### Miembros
La lista propiamente cuenta con sus propios métodos y miembros. Entre sus miembros encontramos los valores privados de tamaño, una apuntador al nodo inicial y otro al nodo final.<br>
```c++
Node *m_head; 
Node *m_tail; 

int m_size;
```

### Iniciador <br>
Pone el tamaño a cero, crea el nodo inicial y final, y los apunta entre si. <br>
```c++
void init(){
    m_head = new Node();
    m_tail = new Node();
    m_size = 0;

    m_head->m_next = m_tail;
    m_head->m_previous = nullptr;

    m_tail->m_next = nullptr;
    m_tail->m_previous = m_head;
}
```
### Insertar elemento

Inserta un elemento en la lista, ya bien sea mediante la posición dada por un iterador o una posición numérica en la lista.<br>
```c++
iterator insert(iterator itr, const Type &object) {
    Node *p = itr.m_current;
    m_head->m_next = new Node{object, m_head->m_next};
    m_size++;
    return iterator(m_head->m_next);
}

void insert(int position, const Type &object){
        insert(generateIterator(position),object);
    }
```
### Eliminar elemento

Elimina un elemento mediante un iterador o un numero de \
```c++
  iterator erase(iterator itr){

    if(itr == End()){
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

void erase(int position){
    erase(generateIterator(position));
}
```

### Generar iterador

Las funciones de eliminar e insertar un elemento se ven apoyadas por el método *generateIterator()* el cual transforma un entero en una posición de la lista.<br>
```c++
   iterator generateIterator(int position){
        
        if(position<0 || position>m_size+1){
            throw std::logic_error("Trying to generate an out of bounds iterator")
        }
        else{
            iterator posIter = Begin();
            for(int i = 0; i != position; i++){
                posIter++;
            }

        return  posIter;   
        }
        
    }
```

### Agregar elemento

Agrega un elemento al final de la lista
```c++
 void push_back(const Type &object){
        Node *aux = m_tail->m_previous;
        m_tail->m_previous = new Node(object,m_tail,aux);
        aux->m_next = m_tail->m_previous;
        m_size++;
    }
``` 
Agregar al inicio de la lista.<br>
```c++
  void push_front(const Type &object){
        Node *aux = m_head->m_next;
        m_head->m_next = new Node(object,aux,m_head);
        aux->m_previous = m_head->m_next;
        m_size++;
    }
```

### Limpiar

Elimina todos los elementos de la lista<br>

```c++
 void clear(){
        while (!IsEmpty()){
            pop_front();
        }
    }
```

### Imprimir 

Imprime todos los elementos de la lista.<br>
```c++
 void print(){
        iterator itr = Begin();
        while (itr != End()){
            std::cout << *itr << " ";
            itr++;
        }
        std::cout << std::endl;
    }
```
### *Getters*

Regresan los miembros privados encontrados en la lista<br>

```c++
    iterator Begin() { return m_head->m_next; }

    iterator End() { return m_tail; }

    int Size() { return m_size;}

    bool IsEmpty() const { return m_size == 0; }
```
