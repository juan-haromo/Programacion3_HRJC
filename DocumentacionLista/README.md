# Clase SLList <br>

La clase SLList es una plantilla de tipo ADT la cual acepta cualquier tipo de dato y sirve para mantener una estructura de datos ordenada con multiples miembros.<br>
Este contenedor es de tipo lista por lo cual podremos expulsar miembros al principio y agregar otros al final.<br>
Asi mismo contamos con la opción de vaciar completamente la lista.<br>
Dentro de esta lista ademas contamos con los nodos centinelas, cabeza y cola para marcar el inicio y el final de la lista.<br>
En esta clase ademas encontramos métodos para imprimir toda la lista, inicializara, obtener su tamaño, si esta o no vacía asi como la implementación de constructores y destructores.<br>

Para esta clase ademas necesitaremos una clase anidada y una estructura anidada.<br>

## Nodo <br>

Los nodos son la estructura anidada que encontramos dentro de esta clase<br>

### Código <br>
```c++
    struct Node  {

        Object data; 
        Node *next; 

        Node(const Object &d = Object{}, Node *n = nullptr)
            : data{d}, next{n} {}

        Node(Object &&d, Node *n = nullptr)
            : data{std::move(d)}, next{n} {}
    };
```
#### Miembros

* Dentro de esta encontramos un ***Object data*** el cual es una plantilla la cual guarda la información del tipo correspondiente.<br>
* Otro de sus miembros es el puntero ***Node \*next*** el cual guarda una referencia al siguiente nodo y permite avanzar en la lista. <br>

#### Constructores
Esta estructura también cuenta con un constructor por copia y uno por referencia, en los cuales los parámetros que no sean pasados se igualaran a nulos.<br>


## Iterador <br>

Esta es la clase publica anidada de la lista. Es la encargada de recorrer los miembros de la lista.<br>

### Código <br>
```c++
public:
    //Clase anidada publica iterador
    class iterator {
    public:

        iterator() : current{nullptr} {} 

        Object &operator*() {
            if(current == nullptr)
                throw std::logic_error("Trying to dereference a null pointer.");
            return current->data;
        }

        iterator &operator++() {
            if(current){
                current = current->next;
            }    
            else
                throw std::logic_error("Trying to increment past the end.");
            return *this;
        }


        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }

    private:
        Node *current; 
        iterator(Node *p) : current{p} {} 
        
        friend class SLList<Object>;
    };
```

#### Miembros

* ***Node \*current***: Es un apuntador hacia el nodo de la lista en el que se encuentra actualmente. <br>

#### Constructores <br>

* Constructor implícito: Instancia un objeto iterador con su puntero en nulo. Es publico.

* Constructor por explicito: Recibe un puntero de un nodo, al cual igualara su propio puntero. Es privado.<br>

#### Operadores

* ***Operador \****: Permite que la clase tenga función de un puntero, si se emplea este operador se regresa el nodo actual si este existe.<br>

* ***Operador ++***: Si existe un nodo siguiente al actual se avanza a ese nodo.<br>

* ***Operador ==***: Revisa si ambos iteradores apunta a la misma dirección de memoria (*true*) o distinta (*false*) <br>

* ***Operador !=***: Revisa si ambos iteradores apuntan a distinta dirección de memoria (*true*) o a la misma (*false*). <br>

#### Clases amigas

* La clase SLList es amiga de la clase iterador.<br>

## SLList

Clase principal que controla la lista.<br>

### Código

```c++
public:

    SLList() : head(new Node()), tail(new Node()), theSize(0) {
        head->next = tail;
    }

    ~SLList() {
        clear();
        delete head;
        delete tail;
    }


    iterator begin() { return {head->next}; } 
    iterator end() { return {tail}; } 

    int size() const { return theSize; }

    bool empty() const { return size() == 0; }

    void clear() { while (!empty()) pop_front(); }

    Object &front() {
        if(empty()){
            throw std::logic_error("List is empty.");
        } 
        return *begin();
    }


   void push_front(const Object &x) { insert(begin(), x); }

    
    void push_front(Object &&x) { insert(begin(), std::move(x)); }

    void pop_front() {
        if(empty())
            throw std::logic_error("List is empty.");
        erase(begin());
    }


    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.current;
        head->next = new Node{x, head->next};
        theSize++;
        return iterator(head->next);
    }

  
    iterator insert(iterator itr, Object &&x) {
        Node *p = itr.current;
        head->next = new Node{std::move(x), head->next};
        theSize++;
        return iterator(head->next);
    }

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
    
 
    void init() {
        theSize = 0; 
        head->next = tail; 
    }
```
#### Miembros

* ***Node \*head*** Guarda el nodo centinela cabeza que marca el inicio de la lista.<br>
* ***Node *tail** Guarda el nodo centinela cola que marca el final de la lista.<br>

#### Constructores 

*  ***Constructor implícito***: Crea una lista vacía de tamaño 0, un nodo cabeza y uno cola apunta el siguiente nodo de la cabeza al nodo cola.<br>

*  ***Destructor*** Vacía la lista con el método clear, después borra el nodo cabeza y cola

#### Métodos

* ***iterator begin()*** Regresa el siguiente nodo a la cabeza.<br>
* ***iterator end()*** Regresa el nodo cola.<br>
*  *** int size()*** Regresa el tamaño de la lista.<br>
* ***Object &front()*** Si la lista no esta vacía regresa su primer elemento.<br>
* ***bool empty()*** Comprueba si la lista contiene o no algún elemento.<br>
* ***void push_front(const Object &x)*** Inserta un nodo en la posición frontal usando la función para insertar y un iterador que apunta al frente con el método begin.<br>
* ***void push_front(Object &&x)*** Inserta un nodo en la posición frontal usando la función para insertar y un iterador que apunta al frente con el método begin.<br>
* ***void pop_front()*** Elimina el elemento de la lista usando la función de borrar y un iterador que apunta al frente con el método begin. Si la lista esta vacía da un error lógico, ya que no hay nada que borrar.<br>
*  ***iterator insert(iterator itr, const Object &x)***  Inserta el objeto *x* en la posición que apunta el iterador.<br>
* ***iterator insert(iterator itr, Object &&x)*** Mueve el objeto *x* en la posición que apunta el iterador.<br>
* ***iterator erase(iterator itr)*** Borre el elemento al que apunta el iterador parámetro.<br>
* ***void printList()*** Imprime todos los elementos de la lista. <br>
* *** void init()*** Inicializa la lista con un tamaño 0 y con el nodo cabeza apuntando al cola como siguiente.<br>
