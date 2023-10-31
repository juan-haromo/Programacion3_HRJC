# Listas 

Las listas son un tipo de estructura ADT, las cuales constan de *nodos* que guardan información y referencias a otros nodos en la lista, estos suelen ser al siguiente o al anterior.<br>
Para desplazarnos por los nodos que contiene una lista empleamos *iteradores*.<br>
Mientras que para marcar el inicio y final de una lista usamos un par de nodos centinelas llamados *head* y *tail*.<br>

## Lista enlazada 

Es un tipo de lista en el cual los nodos cuentan con un único puntero al siguiente miembro de la lista, por lo cual solo se puede avanzar hacia adelante en la misma.<br>

### Estructura anidada *Nodo* (privado)

```c++
   //Estructura anidada privada nodo
    struct Node  {

        Type m_data; //Guarda la información del tipo correspondiente
        Node *m_next; //Puntero al siguiente nodo de la lista

        //Constructor por defecto y por copia -- Implícito
        //Si se proporciona un objeto y su puntero estos serán guardados en m_data y m_next
        //Si no se proporciona, se guardara un objeto vació en m_data y un puntero nulo en m_next
        Node(const Type &data = Type{}, Node *next = nullptr)
            : m_data{data}, m_next{next} {}

        //Constructor de referencia
        //Recibe un nodo como parámetro, con el cual cambia sus parámetros m_data y m_next
        Node(Type &&data, Node *next = nullptr)
            : m_data{std::move(data)}, m_next{next} {}
    };
```

Guarda la información de tipo template, por lo cual puede recibir cualquier tipo de dato primitivo.<br>
Ademas de un puntero hacia el siguiente miembro de la lista.<br>
Cuenta con dos constructores, por copia y referencia, para poder recibir tanto *r* como *l* valores.<br>
Es una estructura privada, solo accesible dentro de la propia clase.<br>

### Clase anidada *iterador* (publico)


#### Miembros

```c++
private:
    Node *m_current; //Guarda un puntero al nodo actual
```
#### Clases amigas

```c++
    friend class SLList<Type>; //La plantilla SLList<Type> puede acceder también los miembros privados y protegidos 

```
#### Constructor 
```c++  
public:
    iterator() : m_current{nullptr} {} //Constructor por defecto. Implícito  Inicia su valor puntero como nulo
private:
    iterator(Node *current) : m_current{current} {} //Constructor con parámetro. Recibe un nodo como parámetro al cual apunta su apuntador

```
Cuenta con un constructor publico y privado.<br>
El constructor privado permite crear un iterado que apunte a un nodo especifico.<br>

#### Operadores

```c++
public:
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
    //Lleva el conteo del nodo en el que se encuentra 
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
```

### Constructor SLList (publico)

```  c++
    //Constructor implícito
    /*
    Crea una lista vacía de tamaño 0
    Crea un nodo cabeza y uno cola
    Apunta el siguiente nodo de la cabeza al nodo cola
    */
    SLList() : m_head(new Node()), m_tail(new Node()), m_size(0) {
        m_head->m_next = m_tail;
    }
```

### Destructor SSList (publico)

```c++ 
    //Destructor
    //Vacía la lista con el método clear
    //Después borre el nodo cabeza y cola
    ~SLList() {
        clear();
        delete m_head;
        delete m_tail;
    }
```

### *Getters* (públicos)

```c++
    //Inicio regresa el siguiente nodo a la cabeza
    iterator begin() { return {m_head->m_next}; } 

    //Final regresa el nodo cola
    iterator end() { return {m_tail}; } 

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
```

### Métodos  

#### Insertar al frente  (publico)
```c++
    //Insertar al frente copia
    //Inserta un nodo en la posición frontal usando la función para insertar y un iterador que apunta al frente con el método begin
    void push_front(const Type &data) { insert(begin(), data); }

    //Insertar al frente referencia
    //Inserta un nodo en la posición frontal usando la función para insertar y un iterador que apunta al frente con el método begin
    void push_front(Type &&data) { insert(begin(), std::move(data)); }

```

#### Inserta por referencia en una posición (publico)

```c++
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
```
Complejidad $O(N)$

#### Inserta por copia en una posición (publico)

```c++
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
```

Complejidad $O(N)$

#### Borrar (publico)

``` c++   
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
```

Complejidad $O(N)$

#### Imprimir (publico)

```c++
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
```
Complejidad $O(N)$

#### Inicializar (privado)

```c++
    //Inicializado de la lista
    void init() {
        m_size = 0; //Tamaño por defecto
        m_head->m_next = m_tail; //Si la lista esta vacía el siguiente elemento del inicio es el final
        m_tail->m_next = nullptr;
    }
```

Complejidad $O(1)$

Método usado por el constructor para inicializar la estructura

### Miembros 

```c++
    //Miembros privados
    Node *m_head; //Apuntador al inicio de la lista
    Node *m_tail; //Apuntador al final de la lista
    int m_size;//Tamaño de la lista
```

## Lista doblemente enlazada *DLList*

Es un tipo de lista en el cual los nodos cuentan con un  puntero al siguiente y uno al anterior miembro de la lista, por lo cual  se puede avanzar hacia adelante y hacia atrás en la estructura.<br>

### Estructura anidada nodo (protegida)

```c++
    protected: struct Node{

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
```
Este nodo guarda su información, un puntero hacia el siguiente y anterior nodo.<br>
Cuenta con un constructor por copia y uno por referencia.<br>
La estructura es protegida, ya que nos interesa que su clases hijas (stack y queue) puedan acceder a la misma.<br>

### Clase anidada iterador (publico)

#### Constructor 
```c++
    public:
        //Constructor implícito
        //Inicia su puntero como nulo
        iterator() : m_current{nullptr}{}
    protected:
        //Constructor con parámetro
        //Recibe el puntero de un nodo al cual iguala su propio puntero
        iterator(Node *current) : m_current{current}{}
```

####  Destructor 

```c++
    ~iterator() = default;
```

Se emplea el constructor por defecto

#### Operadores

```c++
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
```
#### Miembros

```c++
        //Puntero al nodo actual
        Node *m_current;
```

#### Clase amiga

```c++
    //La clase DDList puede acceder a los miembro privados
    friend class DLList<Type>;
```
### Constructor lista (publico)

```c++
    //Constructor implícito
    //Inicializa la lista
    DLList() { init(); }
```

### Destructor lista (publico)

```c++
    //Destructor
    //Vacía la lista y elimina los nodos cabeza y cola
    ~DLList(){
        clear();
        delete m_head;
        delete m_tail;
    }
```

### Métodos  

#### Insertar por copia con referencia (publico)

```c++
    //Insertar con iterador
    //Recibe un iterador y un objeto
    //Inserta el objeto en la posición del iterador
    iterator insert(iterator position, const Type &object) {
       Node *p_current = position.m_current;
       m_size++;
       return {p_current->m_previous = p_current->m_previous->m_next = new Node{object,p_current,p_current->m_previous}};
    }
```

Complejidad $O(1)$

#### Insertar con generación de iterador (publico)

```c++
   //Insertar con posición 
    //Recibe un entero y un objeto
    //En la posición indicada se genera un iterador y se inserta el objeto 
    void insert(int position, const Type &object){
        insert(generateIterator(position),object);
    }
```
Complejidad $O(1)$

#### Insertar por referencia (publico)

```c++
    //Insertar por referencia
    //Recibe un iterador y una referencia
    iterator insert(iterator position, Type &&object) {
      Node *p_current = position.m_current;
       m_size++;
       return {p_current->m_previous = p_current->m_previous->m_next = new Node{std::move(object),p_current,p_current->m_previous}};
    }
```

Complejidad $O(1)$

#### Insertar por referencia con generación de iterador (publico)

```c++
    //Insertar por referencia
    //Recibe un entero y una referencia
    void insert(int position, const Type &&object){
        insert(generateIterator(position),object);
    }
```
Complejidad $O(N)$


#### Generar iterador (publico)

```c++
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
```

Convierte un entero en un iterador moviendo "X" posiciones a partir del inicio de la lista.<br>

Complejidad $O(N)$

#### Agregar por copia al final (publico)

```c++
    //Agregar al final por copia usando el método insertar 
    //Agrega un elemento al final de la lista
    void push_back(const Type &object){
        insert(end(),object);
    }
```
Complejidad $O(1)$

#### Agregar al final por movimiento (publico)

```c++
    //Agregar al final por referencia usando el método insertar
    //Agrega un elemento al final de la lista
    void push_back(Type &&object){
       insert(end(),std::move(object));
    }
```
Complejidad $O(1)$


#### Agregar al inicio por referencia (publico)

``` c++
    //Agregar al inicio por referencia usando el método insertar 
    //Agrega un elemento al inicio de la lista
    void push_front(Type &&object){
       insert(begin(),std::move(object));
    }    
```

Complejidad $O(1)$

#### Eliminar al inicio (publico)


```c++
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
```

Complejidad $O(1)$

#### Eliminar al final (publico)

```c++
   void pop_back(){
          if(IsEmpty()){
            throw std::logic_error("List is empty");
        }
        else{
          erase(end().m_current->m_previous);
        }
    }
```

Complejidad $O(1)$

#### Borrar (publico)
```c++
   void pop_back(){
          if(IsEmpty()){
            throw std::logic_error("List is empty");
        }
        else{
          erase(end().m_current->m_previous);
        }
    }
```
Complejidad $O(1)$

#### Borrar con generación de nodo (publico)

```c++
    //Borrar
    //Borra el elemento en la posición indicada
    void erase(int position){
        erase(generateIterator(position));
    }
```
Complejidad $O(N)$

####  Limpiar (publico)

```c++
    //Limpiar
    //Elimina todos los elementos de la lista usando el método pop front
    void clear(){
        while (!IsEmpty()){
            pop_front();
        }
    }
```
Complejidad $O(N)$

#### Imprimir  (publico)

```c++
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
```
Complejidad $O(N)$

#### Inicializar (privado)

```c++
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
```
Complejidad $O(1)$

### Getters

```c++
    //Regresa el inicio de la lista
    iterator begin() { return m_head->m_next; }

    //Regresa el final de la lista
    iterator end() { return m_tail; }

    //Regresa el tamaño de la lista
    int size() { return m_size;}

    //Regresa si la lista esta o no vacía
    bool IsEmpty() const { return m_size == 0; }
```

### Miembros protegidos 

```c++
    Node *m_head; //Nodo inicial
    Node *m_tail; //Nodo final

    int m_size; //Tamaño de la lista
```

## *Stack*

Es un tipo de lista doblemente enlazada en la cual se restringen los métodos de insertar y eliminar elementos, siendo que solo se pueden insertar elementos en el final de la estructura y solo eliminar elementos al final de la estructura. Por lo cual solo se puede interactuar con un elemento a la vez, a este elemento se le conoce como top.<br>
Esta sigue el concepto de ***LIFO*** o Last Input, First Output<br>

Debido a que es un derivado de la lista doblemente enlazada, heredaremos a partir de dicha clase en forma privada, por lo cual contamos con los nodos e iteradores de la DLList, ademas solo daremos acceso especifico a las funciones  que necesita *stack*<br>

### Constructor 

```c++
//Constructor explicito
Stack(){
    DLList<Type>::init();
}
```

Usamos la función del init constructor de DLList para inicializar el stack.<br>

### Destructor 

```c++
  //Destructor
    ~Stack(){
        clear(); //Limpiamos la lista
        //Eliminamos ambos nodos centinelas
        delete DLList<Type>::m_head; 
        delete DLList<Type>::m_tail;
    }
```

Usamos la misma secuencia de funciones del destructor de DLList para el destructor de stack.<br>

### Métodos

#### Agregar por referencia (publico)

```c++
    //Agregar un elemento por referencia
    void push(Type &data){
        DLList<Type>::push_back(data); //Usamos la función push back que agrega un elemento al final
    }
```

Complejidad $O(1)$


#### Agregar por copia (publico)

```c++
    //Agregar un elemento por copia
    void push(Type &&data){
        DLList<Type>::push_back(std::move(data)); //Usamos la función push back que agrega un elemento al final
    }
```
Complejidad $O(1)$

#### Imprimir  (publico)

```c++
   //Imprimir
    void print(){
        DLList<Type>::print(); //Imprimimos usando el método imprimir de la DLList
    }
```
Complejidad $O(N)$

#### Pop (publico)
```c++
    //Pop
    void pop(){
       DLList<Type>::pop_back(); //Eliminamos el ultimo elemento del stack usando el pop bka c de la DLList
    }
```
Complejidad $O(1)$

#### Limpiar (publico)

```c++
    //Limpiar
    void clear(){
        DLList<Type>::clear();//Limpiamos el stack usando la función limpiar de la DLList
    }
```
Complejidad $O(N)$

#### Top (publico)

```c++
    Type top(){
        return DLList<Type>::m_tail->m_previous->m_data; //Regresamos la información del elemento que se encuentra en el top del stack
    }
```
Complejidad $O(1)$

## *Queue*

Es un tipo de lista doblemente enlazada en la cual se restringen los métodos de insertar y eliminar elementos, siendo que solo se pueden insertar elementos en el final de la estructura y solo eliminar elementos que se encuentren al inicio de la misma.<br>

Esta estructura sigue el concepto de ***FIFO** o First Input, First Output.<br>

Debido a que es un derivado de la lista doblemente enlazada, heredaremos a partir de dicha clase en forma privada, por lo cual contamos con los nodos e iteradores de la DLList, ademas solo daremos acceso especifico a las funciones  que necesita *queue*<br>


### Constructor 

```c++
 //Constructor explicito
    Queue(){
        DLList<Type>::init();
    }
```


### Destructor 

```c++
  //Destructor 
    ~Queue(){
        clear();//Limpiamos la queue
        //Eliminamos los nodos centinelas
        delete DLList<Type>::m_head;
        delete DLList<Type>::m_tail;
    }
```
### Métodos  

####  Enfilar por copia (publico)

```c++
  //Enfilar
    //Agrega un elemento al final de la fila copia
    void enqueue(Type &data){
        DLList<Type>::push_back(data); //Usamos la función pop back de DLList que agrega un dato al final 
    }
```
Complejidad $O(1)$

#### Enfilar por referencia  (publico)

```c++
    //Enfilar
    //Agrega un elemento al final de la fila referencia
    void enqueue(Type &&data){
        DLList<Type>::push_back(std::move(data));  //Usamos la función pop back de DLList que agrega un dato al final 
    }
```
Complejidad $O(1)$

#### Des-enfilar (publico)

```c++
    //Des-enfilar
    //Sacamos el primer elemento de la fila
    void dequeue(){
        DLList<Type>::pop_front(); //Usamos la función pop_front de la DLList que elimina el primer elemento de la lista
    }
```
Complejidad $O(1)$
 
#### Imprimir  (publico)

```c++
    /Imprimir
    //Imprimimos la queue
    void print(){
        DLList<Type>::print(); //Usamos la función de imprimir de la DLList
    }
```
Complejidad $O(N)$

#### Front  (publico)
 
```c++
    //Front
    //Regresamos el primer elemento de la lista
    Type front(){
        return DLList<Type>::m_head->m_next->m_data;
    }   
```
Complejidad $O(1)$

#### Limpiar (publico)

```c++
    //Limpiar
    //Limpiamos la lista
    void clear(){
        DLList<Type>::clear(); //Borramos todos los elementos de la lista usando la función clear de DLList
    }
```
Complejidad $O(N)$