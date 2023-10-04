# Listas, Pilas y colas<br>

## Tipos de datos abstractos (***ADTs***)<br>

Son abstracciones matematicas, formadas por un grupo de objetos con operaciones.<br>
Algunas de estas abstracciones son listas y grapos, junto a sus operaciones.<br>
Cualquier tipo de operacion puedse ser usada para cualquier tipo de ADT , pero la eleccion dse esta depende del diseno del programa.<br>

## Listas ADT <br>

> "Una *lista* (tambien llamada *array*) es una secuencia de varias variables agrupadas bajo el mismo nombre... Se define un solo nombre de variable "*x*" y cse puede acceder a las variables usando brackets de la siguiente manera x\[i]  donde im, es la posicion en la lista... El tamano de la lista es N con N >= 0, donde los indices van de 0 a N-1 "
>
> \[1]	“13: Lists (arrays)”, Uwaterloo.ca. [En línea]. Disponible en: https://cscircles.cemc.uwaterloo.ca/13-lists/. [Consultado: 01-oct-2023].

Los elementos de una lista pueden ser te tipos basicos como int o char, o de clases complejas.<br>

En estas listas existen funciones basicas como imprimirla, vaciarla, agregar o eliminar un elemento, pero se pueden agreagar o modificar de acuerdo a lo que se necesite asi como tratar con casos especiales.<br>

### Implementacion mediante arreglos<br>

Las funcionalidades de las listas pueden senr implementadas mediante arreglos con una capacidad establecida, o con vectores que permiten aumentar su capacidad.<br>
De esta forma se obtienen implementaciones como el imprimir la lista con una complejidad linear y una busqueda con una constante constante, sin embargo si se necesitan hacer inserciones o deleciones que no sean al final de la lista la complejidad es $O(N)$ mientras que si es la final es de tan solo $O(1)$. Por lo cual si las inserciones y deleciones son al final de la lista, los arreglos son funcionales, mientras que si ocurren a lo largo de la lista, no lo son.<br>

### Listas vinculadas<br>

Para evitar el costo lineal de la insercion y la delecion, las listas no debe estar almacenada de forma continua, ya que de lo contrario se tendria que mover una parte de la lista<br>
Como solucion a este problema existen las listas vinculadas.Estas son una serie de nodos, los cuales no tienen que ser adyacentes en memoria. Estos nodos contienen una parte que apunta al siguiente nodo, mientras que el ultimo miembro de la lista apunta a un elemento *null*.<br>


```c++
//Lista vinculada simplificada en una clase nodo.
class Node{
    public: 
        Node(int newData){
        data = newData;
        next = nullptr; //Inicia en nulo, suponiendo que siempre se es el ultimo de la lista
        }
        void AddNext(const Node &newNextNode){
        next = newNextNode; // Asigna el siguiente miembro de la lista a otra objeto node
        }

    private: 
    
        int data; //Datos propios de la clase
        Node *next; //Guarda un puntero al siguiente nodo en la lista
    
}
```
> \[2]	Palistha, “How does a Linked List work? A beginner’s guide to linked lists”, freecodecamp.org, 12-may-2023. [En línea]. Disponible en: https://www.freecodecamp.org/news/how-linked-lists-work/. [Consultado: 02-oct-2023].

Mientras que con este metodo encontramos que operaciones como imprimir o encontrar un elemento se vuelven lineales, las funcionalidades de eliminar o agregar un elemento a la lista tiene un tiempo constante, ya que no se requiere mover todos los elementos, sino que solo es necesario mover un par de vinculos.<br>
Tambien existen las listas doblemente vinculadas, donde no solo se guarda un vinculo al siguiente elemento, sino que tambien se tiene vinculo al elemento anterior.<br>

## Vector y listas en c++ STL 

En c++ existe una parte dedicada a la implementacion de estructuras de datos comunes, esta comunmente se conoce como Libreria estandar de plantillas (*Standard Templete library* ***STL***).<br>
En esta, hay 2 implementaciones comunes de las listas *ADT*:<br>

### Vector 
Es una lista expandible con un capacidad de indexacion constante. La desventaja de este es que la insercion y la delecion, a menos que sean hechos al final del vector son costosas.<br>

### Lista 
La lista provee una implementacion doblemente vinculada de las listas ADT, la ventaja de esta es que la insercion y delecion de elementos son baratas, pero no es facil indexar este tipo.<br>

### Caracteristicas de las listas y vectores

1. Tanto la lista como los vectores son ineficientes para busquedas.<br>
2. Ambos son *templates* por lo cual deben se instanciados con el tipo de objetos que almacenaran.<br>
3. Comparten metodos de las STL:<br>
    3.1 int size() : regresa el numero de elementos en el contenedor.<br>
    3.2 void clear() : elimina todos los elementos del contenedor.<br>
    3.3 bool empty() : dice si el contenedor esta o no vacio.<br>
4. PUeden agregar/eliminar elementos del final de la lista con un tiempo constante.<br>
    4.1 void push_back(const object & x) : agrega *x* al final de la lista.<br>
    4.2 void pop_back() elimina el objeto al final de la lista.
    4.3 const Object & back() : regresa el objeto al final de la lista o su referencia si se provee.<br>
    4.4 const Object & front() : : regresa el objeto al principio de la lista o su referencia si se provee.<br>

### Metodos de las listas <br>
Debido a que las listas son doblemente vinculadas cuentan con los siguientes metodos que los vectores no tienen:<br>
1.  void push_front(const Object & x) : Agrega *x* al principio de la lista.<br>
2. void pop_front( ) : Elimina el primer elemento de la lista<br>

### Metodos de los vectores
1. Operador \[index] : regresa el objeto encontrado en el indice proporcionado, sin efectuar *bounds-checking*.<br>
2. Object & at( int idx ) : regresa el objeto en el indice indicado, realizando *bounds-checking*.
3. int capacity() : regresa la capacidad interna del vector.<br>
4.  void reserve(int newCapacity): fija una nueva capacidad para el vector.<br>

> ***bounds-checking*** <br>
>
>"Se le llama asi a cualquier metodo que revisa que la variable dada se encuentre en los parametros antes de ser usada. Esto incluye el asegurarse quue el numero se encuentre en un rango valido (*range checking*), asi como el que el indice se encuentre dentro de los limites de un arreglo (*index checking*)."<br>
>
>"En caso de no estarlo, se regresara un error"<br>
>
>\[3] “Bounds checking”, Embedded Artistry, 16-may-2020. [En línea]. Disponible en: https://embeddedartistry.com/fieldmanual-terms/bounds-checking/. [Consultado: 02-oct-2023].

### Iteradores 

Algunas operaciones en listas, requieren de la nocion de la posicion, la cual se representa con un tipo anidado, los *iteradores*. Para las listas list\<type>::iterator y vector\<type>::iterator para vectores.

#### Obteniendo un iterador
Para esto podemos usar un par de metodos 
* iterator begin() : regresa un iterador el cual representa el primer objeto de la lista.<br>
* iterator end( ) : regresa un iterador que representa el final de un contenedor, generalmente en una posicion despues del ultimo miembro de la lista.<br>

#### Metodos de los iteradores
* Pueden ser comparados mediante == y !=.<br>
    * == regresa *verdadero* si apuntan a la misma direccion y *falso* si no apuntan a la misma direccion, y 
    * != regresa *verdadero* si no apuntan a la misma direccion y *falso* si apuntan a la misma direccion
* Cuentan con un constructor por copia mediante el operador =.<br>
* iterator++ y ++iterator avanzan al siguiente miembro.<br>
* *iteraror regresa una referencia al objeto guardado en la locacion del iterador.<br>

#### Operaciones en contenedores que requieren un iterador

* iterator insert(iterator pos, const Object & x) : agrega x en la siguiente posicion a la dada por el iterador. Es de tiempo consante para listas, pero no para vectores.<br>
* iterator erase(iterator pos) : elimina el objeto guardado en la posicion del iterador. Es de tiempo consante para listas pero no para vectores.<br>
* iterator erase(iterator start, iterator end) : elimina todos los elementos desde el iterador de inicio hasta uno antes del final (ya que este esta una posicion mas arriba). Si se quiere borrar toda un contenedor con este metodo se hace facilmente con c.erase(c.begin(), c.end()).<br>

#### Iteradores constantes <br>

Si en una funcion se realiza un paso por referencia constante de una contenedor (lista, vector etc...) y se emplea un iterador para operarlo, este puede llegar a hacer cambios, anulando asi el proposito del paso constante. Para evitar este conflicto, se pueden usar const_iterator, los cuales regresan una referencia constante por lo que no pueden ser lhs, y por lo tanto no ser modificado.<br>
Pese a ser constante, esto solo es en la referencia que regresan por lo cual aun pueden ser reasignados a otros valores y usar metodos como beging() y end().<br>

## Implementacion de Vector <br>

Implementacion de una clase copia de la clase vector encontrada en el STL de c++.<br>

```c++
#include <algorithm>

template <typename Object>

class Vector{
    public:
       
        typedef Object * iterator;
        typedef const Object * const_iterator;
        static const int SPARE_CAPACITY = 16;

        //Constructores 

        //Constructor por defecto
        /*
        Asigna el valor del parámetro al tamaño del vector, si no se proporciona a uno este se pone en 0 por defecto.
        Asigna la capacidad del vector a su tamaño + una capacidad extra, de 16 en este caso.
        Asigna el iterador del inicio a uno nuevo con la capacidad creada
        */
        explicit Vector(int initSize = 0) : theSize{initSize},
        theCapacity{ initSize + SPARE_CAPACITY}
        {objects = new Object[theCapacity];}

        //Constructor por copia
        /*
        Copia el tamaño del rhs al lhs.
        Realiza lo mismo con la capacidad.
        Asigna el iterador de inicio a uno nuevo con la capacidad copiada.
        Copia cada uno de los miembros del rhs al lhs en su respectiva posicion.
        */
        Vector( const Vector & rhs ) : theSize{ rhs.theSize },
        theCapacity{ rhs.theCapacity }, objects{ nullptr } 
        {
        objects = new Object[ theCapacity ];
        for( int k = 0; k < theSize; ++k ){
           objects[ k ] = rhs.objects[ k ];//Copia de los miembros del rhs al lhs 
            } 
        }

        //Destructor
        //Elimina todos los objetos contenidos en el iterador objetos
        ~Vector( )
        { delete [ ] objects; }

        //Constructor de movimiento
        /*
        Copia los valores de tamaño, capacidad y los objetos del rhs al lhs.
        Posteriormente regresa los valores del rhs a nulos o 0 segun el caso.
        */
        Vector( Vector && rhs ) : theSize{ rhs.theSize },
        theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
        {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
        }



        //Operadores

        //Operador = 
        //Crea una copia del rhs, la cual mediante swap mueve hacia el lhs, haciendo que ambos sean copias exactas.
        Vector & operator= ( const Vector & rhs ){
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
        }

        //Operador = de movimiento
        /*
        Cambia los valores del rhs y lhs mediante la funcion swap.
        */
        Vector & operator= ( Vector && rhs ){
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );
        return *this;
        }
        
        //Operador []
        //Regresa el objeto encontrado en el indice indicado
        Object & operator[]( int index )
        { return objects[ index ]; }

        
        //Operador [] constante
        //Regresa el objeto encontrado en el indice indicado como una constante 
        const Object & operator[]( int index ) const
        { return objects[ index ]; }



        //Metodos

        //Redimension del vector
        /*
        Si la nueva nueva capacidad es mayor al tamaño actual se reserva el doble de la memoria de la nueva capacidad, para que esta costosa funcion se realize multiples veces.
        Despues el tamaño actual se cambia por el nuevo.
        */
        void resize( int newSize )
        {
            if( newSize > theCapacity ){
                reserve( newSize * 2 );   
            }
        
            theSize = newSize;
        }

        //Reservar memoria
        /*
        Si la nueva capacidad es menor a la actual, no se realiza ninguna operacion.
        Si no lo es entonces se crea un nuevo arreglo auxiliar con la capacidad solicitada.
        Luego se mueven todos los elementos del viejo arreglo al auxiliar. 
        Se guarda la nueva capacidad.
        Se cambia el contenido del arreglo auxiliar al original con el tamaño cambiado. 
        Se libera la memoria del arreglo auxiliar
        */
        void reserve( int newCapacity )
        {
            if( newCapacity < theSize ){
                return;
            }

            Object *newArray = new Object[ newCapacity ];
            for( int k = 0; k < theSize; ++k ){
               newArray[ k ] = std::move( objects[ k ] ); 
            }
            
            theCapacity = newCapacity;
            std::swap( objects, newArray );
            delete [ ] newArray;
        }

       

        //Vacio
        //Si el tamaño del arreglo es igual a 0, este esta vacio, si no lo es no esta vavio
        bool empty( ) const
        { return size( ) == 0; }

        //Tamaño
        //Regresa el tamaño del Vector
        int size( ) const
        { return theSize; }

        //Capacidad
        //Regresa la capacidad del vector
        int capacity( ) const
        { return theCapacity; }

        //Agregar al final
        /*
        Si el tamaño es igual a la capacidad, es decir esta lleno, se reserva memoria extra para poder seguir guardando elementos.
        Una vez con la memoria necesaria se aumenta en uno el tamaño y se guarda el objeto.
        */
        void push_back( const Object & x )
        {
            if( theSize == theCapacity ){
                reserve( 2 * theCapacity + 1 ); 
            }
            
            objects[ theSize++ ] = x;
        }

        //Agregar al final por movimiento. 
        /*
        Si el tamaño es igual a la capacidad, es decir esta lleno, se reserva memoria extra para poder seguir guardando elementos.
        Una vez con la memoria necesaria se aumenta en uno el tamaño y se mueve el objeto del rhs al lhs
        */
        void push_back( Object && x )
        {
            if( theSize == theCapacity ){
                reserve( 2 * theCapacity + 1 );
            }
        
            objects[ theSize++ ] = std::move( x );
        }

        //Eliminar el final
        //Elimina el ultimo elemento de contenedor haciendo mas pequño el tamaño del mismo.
        void pop_back( )
        {
        --theSize;
        }

        //Back
        //Regresa el iterador una posicion
        const Object & back ( ) const
        {
        return objects[ theSize - 1 ];
        }
    
        //Inicio
        //Regresa el primer elemento (0) del contenedor
        iterator begin()
        { return &objects[ 0 ]; }

        //Inicio constante
        //Regresa el primer elemento (0) del contenedor como una referencia constante
        const_iterator begin( ) const
        { return &objects[ 0 ]; }

        //Fin 
        //Regresa un elemento despues de el ultimo del contenedor
        iterator end()
        { return &objects[ size( ) ]; }

        //Fin 
        //Regresa un elemento despues de el ultimo del contenedor como una referencia constante
        const_iterator end( ) const
        { return &objects[ size( ) ]; }
        


    private:
        //Variables
        int theSize;
        int theCapacity;
        Object * objects;
};
```
## Implementacion de listas <br>

Para la implementacion de la listas se necesitan 3 clases:
1. La clase lista que contiene vinculos al principio y fin de la lista  contiene los metodos de la misma. <br>
2. Una clase nodo, que guarde punteros al siguiente y anterior nodo. <br>
3. Iteradores e iteradores constantes para tener nocion de la posicion y su contenido.<br>

Para las listas se suelen crear los llamados *nodos centinelas*, los cuales son *header node* el cual se encuentra al frente de la lista y el *tail node* que se encuentra al final de la fila, estos simplifican el codigo al elminiar casos especiales como el querer eliminar el primer o ultimo elemento de la lista.<br>

```c++
//Nodos 
//Son estructuras ya que solo guardan datos y constructores.
private: struct Node{
    ///Datos
    Object data;
    Node *prev;
    Node *next;

    //Constructor por copia
    Node( const Object & d = Object{ }, Node * p = nullptr,
    Node * n = nullptr )
    : data{ d }, prev{ p }, next{ n}{}
    
    //Constructor por referencia
    Node( Object && d, Node * p = nullptr, Node * n = nullptr )
    : data{ std::move( d ) }, prev{ p }, next{ n}{}
    //Si no se proporciona un objeto al construir el nodo su punteros se igualaran a nulo.
};
```

Esta estructura existira dentro de la clase lista, ya que necesitamos que funcione en esta y que no se alterada de manera externa y solo operada internamente, por lo que la convertimos en privada. <br>

Otra de las funciones necesitadas en las listas son los iteradores, los cuales funcionaran para mantener posiciones de la lista y realizar operaciones.Para esto necesitaremos un iterador constante y un iterador, el cual heradara del constante y solo hara override para cambiar las referencias constantes a modificables, por lo cual solo el constante sera descrito.<br>


```c++
class const_iterator
{
    public:
        //Constructor por defecto
        //Inicializa el puntero current como nulo
        const_iterator() : current{ nullptr }
        {}
        
        //Operador * 
        //Regresa ls informacion del obejeto al cual apunta
        const Object & operator* () const
        { return retrieve( ); }

        //Operador ++ postfijo
        //Apunta el puntero actual al siguiente miembro de la lista
        const_iterator & operator++ (){
        current = current->next;
        return *this;
        }

        //Operador ++ prefijo
        //Mueve el puntero acual a la posicion de anterior y regresa dicho puntero.
        const_iterator operator++ (int){
        const_iterator old = *this;
        ++( *this );
        return old;
        }

        //Operador == 
        //Dice si el nodo rhs es o no el mismo al nodo lhs
        bool operator== ( const const_iterator & rhs ) const
        { return current == rhs.current; }

        //Operador != 
        //Dice si el nodo rhs es o no diferente al nodo lhs
        bool operator!= ( const const_iterator & rhs ) const
        { return !( *this == rhs ); }

    //Miembros protegidos, accesibles solo a la misma calse o clases amigas
    protected:
        //Datos
        Node *current; //Puntero al nodo actual

        Object & retrieve( ) const
        { return current->data; } //Regresa informacion del nodo actual
        
        const_iterator( Node *p) : current{ p } //Cambia el nodo actual
        { }


        friend class List<Object>; //Clase amiga para iterator
};
```

> "Una clase amiga puede accedar a los miembros privados y protejidos de otras clases en la que alla sido declarada como tal."
>
>\[4]	“Friend class and function in C++”, GeeksforGeeks, 03-jun-2014. [En línea]. Disponible en: https://www.geeksforgeeks.org/friend-class-function-cpp/. [Consultado: 03-oct-2023].<br>

Ademas en la clase encontramos los 5 grandes con sus funcionalidades, asi como algunos metodos.<br>

```c++
template <typename Object>
class List
{
    public: 
        //Constructor por defector
        //Inicializa la lista, asignado un nodo cola y uno cabeza y referenciandolos
        List() { init(); }

        //Destructor
        //Borra todos lo elementos de la lista
        //Elimina el nodo cola y cabeza.
        ~List(){
            clear();
            delete head;
            delete tail;
        }

        //Constructor por copia
        //Copia todos los valores contenidos en la lista rhs a la lhs
        List( const List & rhs ){
            init();
            for( auto & x : rhs ){
                push_back( x );
            }
        }

        //Operador =
        //Copia los valores del rhs a una nueva lista,la cual luego cambia sus valores los del lhs
        List & operator= ( const List & rhs ){
            List copy = rhs;
            std::swap( *this, copy );
            return *this;
        }

        //Constructor de movimiento
        //Copia los valores del rhs al lhs
        //Pone los valores del rhs a nulo o 0
        List( List && rhs )
        : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }{
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }

        //Operador = de movimiento
        //Cambia los valores del rhs y lhs
        List & operator= ( List && rhs ){
            std::swap( theSize, rhs.theSize );
            std::swap( head, rhs.head );
            std::swap( tail, rhs.tail );

            return *this;
        }

        //Vaciar lista
        //Mientras la lista no este vacia elimina el elemento del frente
        void clear(){
            while(!empty())
            pop_front();
        }

        //Frente
        //Regrese el objeto al frente de la lista
        Object & front()
        {return *begin( );}

        
        //Frente constante
        //Regrese el objeto al frente de la lista de forma constante
        const Object & front() const
        {return *begin( );}

        //Atras
        //Regresa el elemento anterior al tail, el cual es el ultimo elemento
        Object & back( )
        { return *--end( ); }

        //Atras constante
        //Regresa el elemento anterior al tail de forma constante
        const Object & back( ) const
        { return *--end(); }

        //Agregar al frente
        //Agrega un elemento al frente de la lista mediante un iterador
        void push_front( const Object & x )
        { insert( begin(), x ); }

        //Mover al frente
        //Mover un elemento al frente de la lista mediante un iterador 
        void push_front( Object && x )
        { insert(begin(), std::move(x)); }

        //Agregar al final
        //Agrega un elemento al final de la lista mediante un iterador
        void push_back( const Object & x )
        { insert(end(),x); }

        //Mover al final
        //Mover un elemento al final de la lista mediante un iterador 
        void push_back( Object && x )
        { insert(end(), std::move(x)); }

        //Elimia el elemento al frente de la lista
        void pop_front( )
        { erase(begin()); }

        //Elimia el elemento al final de la lista
        void pop_back()
        { erase(--end()); }

    private: 

        int theSize; //Tamano de la lista
        Node *head; //Puntero al nodo inicial
        Node *tail; //Puntero al nodo final
        //Inicializador
        /*
        Pone el tamano en 0
        Crea los nodos cabeza y cola y los referencia entre si
        */
        void init( ){
            theSize = 0;
            head = new Node;
            tail = new Node;
            head->next = tail;
            tail->prev = head;
        }
}
```
 

## Pila ADT

Una pila es una lista con la restriccion de que las incersiones y deleciones solo pueden ocurrir en la posicion final, llamada *top*.<br>
Las operaciones fundamentales en una pila son:
* Push, que agrega un elemento en *top*.<br>
* Pop, que elimina el elemento *top*.<br>

Los stacks son *LIFO* (last in, first out/ultimo en entrar es el primero en salir).<br>

Las pilas son un tipo de lista, por lo cual cualquier implementacion de lista funciona. Los vectores y listas son opciones viables para esto, pero ocacionalmente sera mejor creear una implementacion especifica. Para estas veces existen dos implementaciones populares.<br>

1. Pilas con listas vinculadas <br>

Se usa una lista simple vinculada. Se hace push en el frente de la lista y pop borrando el elemento en la misma posicion.

2. Pilas con arreglos <br>

Se usan vectores y sus funciones push_back y pop_back y se inicializa con un -1 el cual simboliza un stack vacio. 

### Aplicaciones de las pilas

Se pueden realizar operaciones muy rapidamente, pero de manera limitada. Funcionando para casos como:<br>

1. Revisar simbolos: Revisar que simbolos como () [] y {}, se encuentren correctamente cerrados. Agregando los ([{ al stack y haciendo pop a los }]). Siendo asi que si hay un stack con miembros o se intenta hacer pop a un stack vacio se arrojara un error.<br>

2. Operaciones postfix: Se guardan los elementos en el stack hasta que se tiene que haces una operacion con estos, entonces se les hace pop y el resultado vuelve a ser push en el stack.<br>

3. Cambio de infix a post fix: Guardando los simbolos en el stack hasta encontrar un simbolo de menor jerarquia cuando sera sacado del stack repitiendo este proceso con todos los simbolos hasta cambiar el orden de la operacion. <br>

## Colas ADT

Son listas en las que sus operaciones basicas son el *enqueue*, la cual inserta un elemento al final de la lista; y dequeue el cual elimina y regresa el elemento al inicio de la fila. <br>

### Implementacion <br>

Cualquier implementacion de listas es legal para estas. Se debe mantener un arreglo, la posicion frontal y final del mismo asi como su tamano.<br>
Las operaciones deben ser claras, para *enqueue* un objeto se debe poner en el final del arreglo, representado por *back* y aumentar el tamano del mismo en uno. Para hacer *dequeue* se debe retirar el elemnto frontal, mover el *front* al siguiente elemento del arreglo y disminuir en uno el tamano del mismo.<br>
El problema con esto es que se puede poner el front al final del arreglo, por lo que tecnicamente la siguiente posicion estaria libre, por lo cual la cola estaria libre, por lo cual se suelen usar arreglos circulares, donde no hay ni principio ni fin, sino solo la marca de *front* y *back*.<br>
Aunque existen diferentes formas de manejar esto segun la naturaleza de los datos que se esten trabajando y el diseno que de el programador.<br>

### Aplicaciones de las colas

Algunas de las aplicaciones son: <br>
* Gestionar las solicitudes en una impresora, donde el primero en ser requerido sera el primero en ser atendido (*first come, first serve*).
* La gestion del uso de computadoras en una escuela cuando todas estan ocupatas, teniendo hacer una lista de espera donde se atendera primero a los que llegaron primero.<br>

# Opinion critica <br>

Los tipos de datos abstrasctos (*ADT*) son una parte fundamental de lenguajes como C++, ya que estos permiten organizar y procesar otros tipos de datos que se manejan a lo largo de los programas que en este lenguaje se escriben.<br>
Las implementaciones existentes en la libreria estandar de plantillas (*STL*), son funcionales de manera general, a tal grado que son usadas incluso sin llegar a comprender el como funcionan internamente, gracias a la versatilidad que estas ofrecen. Sin embargo es bueno el comprender como es que estas funcionan ya que de esta manera se pueden llegar a implementar  y modificar este tipo de estructuras de la manera mas conveniente y eficiente para casos especiales y asi obtner el mayor provecho de las mismas. <br>
De ela misma manera encontramos a los iteradores, una estructura anidada de gran funcionalidad ya que nos ayudan a manipular y controlar este tipo de estructuras de manera mas ordenada y segura, las cuales junto a otras estructuras anidadas como los nodos son altamenta utiles para el manejo de datos.<br>
Igualmente el comocer distintos modelos como los vectores, listas, listas vinculadas, pilas y stacks proporciona una idea clara de las distintas maneras en las que estas estructuras se pueden comportar y de los beneficios y desventajas que cada modelo puede ofrecer para asi poder extraer lo que necesitemos de cada uno de ellos e implementarlo de manera correcta.<br>
Por ultimo los Templatesd, un tema ya tradado antes, aqui demuestra la gran capacidad y ventajas que pueden ofrecer, en especial en estrucuras como las pertenecientess a la STL.<br>

# Opinion personal <br>

Despues del capitulo anterior, resumiendo a gran velocidad los temas que desconociamos y rellenando el conocimiento en general, este capitulo a sido mas ameno.<br>
En parte gracias a el capitulo anterior, ya que ademas de lo mencionado anteriormente, sento unas bases solidas las cuales fueron ampliamente usadas, otra vez, por lo cual el aprender y sufrir un poco el capitulo anterior ya ah valido la pena y da ideas de que asi seguira siendo por un tiempo.<br>
Ademas de que estos temas no eran del todo desconocidos, ya que son cosas que habiamos hecho y usado antes, mas sin embargo ahora entiendo el porque hacen lo que hacen, el porque de sus restricciones y de como se emplean. Gracias a esto ahora no solo podre usar estas estructuras de mejor manera sino que tambien tendre la idea de como poder implementar las propias cuando sea necesario.<br>

# Bibliografía

[1]	“13: Lists (arrays)”, Uwaterloo.ca. [En línea]. Disponible en: https://cscircles.cemc.uwaterloo.ca/13-lists/. [Consultado: 01-oct-2023]. <br>
[2]	Palistha, “How does a Linked List work? A beginner’s guide to linked lists”, freecodecamp.org, 12-may-2023. [En línea]. Disponible en: https://www.freecodecamp.org/news/how-linked-lists-work/. [Consultado: 02-oct-2023]. <br>
[3]	“Bounds checking”, Embedded Artistry, 16-may-2020. [En línea]. Disponible en: https://embeddedartistry.com/fieldmanual-terms/bounds-checking/. [Consultado: 02-oct-2023]. <br>
[4]	“Friend class and function in C++”, GeeksforGeeks, 03-jun-2014. [En línea]. Disponible en: https://www.geeksforgeeks.org/friend-class-function-cpp/. [Consultado: 03-oct-2023]. <br>
[5]	M. A. Weiss, Data Structures and Algorithm Analysis in C++, 4a ed. Upper Saddle River, NJ, Estados Unidos de América: Pearson, 2013.
