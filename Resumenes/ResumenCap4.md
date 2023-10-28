# Arboles <br>

Con una gran cantidad de datos, el tiempo de acceso a las listas vinculadas se convierte en una restricción. Por lo que los arboles son una estructura que nos ayuda con el tiempo, al tener una complejidad de $O(logN)$. <br>

## Preeliminares <br>

Un arbol puede ser definido como una coleccion de nodos, en la que si este no se encuentra vacio, consiste de un nodo ***r*** o ***raiz*** el cual cuenta con 0 o mas nodos que forman sub-arboles 

<img src="https://www.oscarblancarteblog.com/wp-content/uploads/2014/08/arbolbinarioperfecto1.png" alt="Arbol binario y no binario" height = "300px" widht = "auto">

Los nodos que surgen a partir de otros son llamados *hijos* (*child* en ingles), a su vez el nodo del que estos salen es llamado *padre* (*parent*), mientras que los nodos que salen del mismo nodo padre son llamados *hermanos* (*sibilngs*).<br>
Todos los nodos, excepto el raiz, tienen un unico nodo padre, mientras que los nodos pueden tener multiples nodos o ninguno. En caso de no tener ningun nodo a estos se les denomian como *hojas* (*leaves*). De la misma manera los hijos de un nodo hijo seran *nietos* para su nodo padre, mientras que este sera el nodo *abuelo* para los mismos.<br>

Un *camino* de un nodo a otro es definido como una secuendcia de nodos n<sub>1</sub>, n<sub>2</sub>, ... n<sub>k</sub>.  
La *longuitud* del camino es el numero de bordes en el camino. <br>  
La *profundidad* de un nodo es lo largo del camino desde el nodo raiz hasta dicho nodo, siendo asi que el nodo raiz tiene una profundidad de 0. <br>
La *altura* de un nodo *n* es la longuitud del camino del nodo *n* al nodo hoja mas lejano. <br>


>Complementario:
> "La ***altura*** de un nodo en un arbol se define como la longitud del camino
más largo que comienza en el nodo y termina en una hoja. La altura de un
nodo hoja será de cero, y la altura de un nodo se puede calcular sumando
uno a la mayor altura de sus hijos..."<br>
>"La ***altura de un árbol*** se define como la altura de su raiz..."<br>
> La ***profundidad de un nodo*** se define como la longitud del camino (único)
que comienza en la raiz y termina en el nodo. La profundidad de la raiz es
cero, y la profundidad de un nodo se puede calcular como la profundidad
de su padre mas uno... A la profundidad de un nodo también se la denomina ***nivel del nodo*** en el
árbol.<br>
>[1]	I. T. I. Gestión, U. De, y V.-D. De Informática, “Estructuras de Datos -Curso 02/03”, Uva.es. [En línea]. Disponible en: https://www.infor.uva.es/~cvaca/asigs/transp3.pdf. [Consultado: 23-oct-2023]. <br>


### Implementacion <br>

Debido a que cada nodo, ademas de su informacion, debe contener un vinculo a sus hijos y hermanos y que estos pueden variar, una forma de declarar los nodos para un arbol es la siguiente:
```c++
template<typename Type>
struct TreeNode{
    Type content;
    TreeNode *firstChild;
    TryNode *nextSibling;
}
```

Con esta implementacion podemos guardar espacio al solo usar los nodos necesarios a la vez que permitimos agregar cuantos se necesiten. <br>

### Arboles transversales y su aplicación <br>

Los arboles tienen una gran variedad de aplicaciones, una de las mas populares y cotidianamente utilizadas son los sistemas de archivos tanto de *UNIX* como de *DOS*, en estos se encuentra un directorio raiz, el cual contiene dentro de si directorios (Los cuales guardan archivos e incluso otros directorios.) y archivos, cumpliendo estos asi con las caracteristicas de los arboles, donde el camino o *path* a cada nodo, siendo asi que dos archivos se pueden llamar de la misma manera y no haber conflicto ya que su *path* es diferente. <br>

#### Pre-orden transversal <br>

En este tipo de orden, el trabajo del nodo es ejecutado antes (*pre*) que sus hijos sean procesados. Siendo asi que primero se trabaja la raiz y despues se hace todo el camino hasta las hojas. <br>

#### Post-orden transversal <br>

En este orden se ejecuta el trabajo de un nodo hasta despues (*post*) de que sus hijos sean procesados. De esta manera se evaluan desde las hojas hasta llegar a la raiz.<br>

## Arboles binarios <br>

Los arboles binarios son aquellos en los que los nodos no pueden llegar a tener mas de 2 nodos hijos. Estos arboles consisten de un nodo raiz y maximo dos hijos, los cuales cumplen con las mismas caracteristicas del nodo raiz.<br>

La profundidad de estos, en promedio suele ser de $O(\sqrt{N})$, mientras que para los arboles de busqueda binaria suele ser de $O(logN)$. Sin embargo la profundidad de esto puede llegar a ser hasta de $N-1$.<br>

### Implementacion <br>

Debido a que este tipo de nodo unicamente cuneta con dos hijos, podemos mantener referencias a ambos dentro del mismo. Por lo que esta estructura guarda un objeto y 2 referencias a sus hijos. (punteros a L y R).

### Ejemplo: Arboles de expresiones 

<img src="https://media.geeksforgeeks.org/wp-content/uploads/expression-tree.png" alt="Árbol de expresiones" height="300px" width="auto">

```c++
//Elementos básicos de un nodo binario
template<typename Type>
struct BinaryNode{
    Type data; //Datos que guarda el nodo
    BinaryNode *left; //Hijo izquierdo
    BinaryNode *right; //Hijo derecho
}
```

El árbol mostrado arriba corresponde a un *Arbol de expresiones*, en donde los nodos hoja son son los operandos, como constantes, variables etc.. Mientras que los otros nodos contienen los operadores.<br>

#### Arbol a expresion
Estos arboles se resuelven de manera recursiva los sub-arboles de derecha a izquiera. En el caso de la imagen se realiza 3 + ((5+9)*2), esta forma de convertir un arbol a una expresion se conoce como: "***inorder transversal***".<br>

Una forma alternativa es imprimir de manera recursiva los sub-arboles isquierdos y despues el operador. Tomando como ejemplo la imagen de ejemplo, la expresion seria: 3 5 9 + 2 * +, esta forma de convertir un arbol a una expresion se conoce como: "***postorder transversal***".<br>

Una tercera forma de imprimir seria, primero los operadores y despues de manera recursiva los sub-arboles izquierdos y luego derechos, de esta forma nuestra expresion seria + 3 * + 5 9 2, esta forma de convertir un arbol a una expresion se conoce como: "***preorder transversal***".<br>

#### Expresion a arbol

Partiendo de una expresion del tipo *postfix* el algoritmo para generar un arbol consta de lo siguiente: <br>
* Si el elemento es un numero (1, 400, PI...), se agrega a un *stack*
* Si el elemento es un operador (*,+,-,/...), los dos ultimos elementos del *stack* pasaran a ser sus hijos y el operador pasara a ser el ultimo elemento del *stack*.

## Arboles de busqueda binaria <br>

Una caracterisica importantes de los arboles binarios, es su aplicacion en busquedas.<br>

Debido a esto para que un arbol binario pueda ser un arbol de busqueda binaria, este debe cumplir con lo siguiente: para todos los elementos de un nodo *X* , todos los elementos en el sub-arbol izquierdo deberan ser menores, mientras que todos los elementos en el sub-arbol derecho deberan ser mayores. <br>

<img src="./Imagenes/ArbolesDeBusquedaBinaria.png" alt="Dos arboles binarios" height="300px" width="auto">

En base a las reglas de al busqueda binaria, el arbol de la izquierda cumple con las caracteristicas, mientras que el de la derecha, no lo hace, ya que si bien 7>4, el problema caen en que 7 se encuentra en el subarbol izquierdo de la raiz (6), lo que implicaria que 7<6>. lo cual es falso, por lo que no puede ser un arbol binario. Pero si quisieramos agregar el nodo 7 y mantener la estructura de arbol binario se veria de la siguiente forma: <br>

<img src="./Imagenes/ArbolBinarioD_Corregido.jpg" alt="arbol binario derecho corregido" height="300px" width="auto">

<br>
Debido a que estas comparaciones se escriben de forma recursiva, lo comun es que la complejidad de la búsqueda, en promedio sea de $O(logN)$.<br>

### Interfaz de un Arbol de Busqueda Binaria <br>


```c++
 template <typename Comparable>
2 class BinarySearchTree
3 {
4 public:
5 BinarySearchTree( );
6 BinarySearchTree( const BinarySearchTree & rhs );
7 BinarySearchTree( BinarySearchTree && rhs );
8 ~BinarySearchTree( );
9
10 const Comparable & findMin( ) const;
11 const Comparable & findMax( ) const;
12 bool contains( const Comparable & x ) const;
13 bool isEmpty( ) const;
14 void printTree( ostream & out = cout ) const;
15
16 void makeEmpty( );
17 void insert( const Comparable & x );
18 void insert( Comparable && x );
19 void remove( const Comparable & x );
20
21 BinarySearchTree & operator=( const BinarySearchTree & rhs );
22 BinarySearchTree & operator=( BinarySearchTree && rhs );
23
24 private:
25 struct BinaryNode
26 {
27 Comparable element;
28 BinaryNode *left;
29 BinaryNode *right;
30
31 BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
32 : element{ theElement }, left{ lt }, right{ rt } { }
33
34 BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
35 : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
36 };
37
38 BinaryNode *root;
39
40 void insert( const Comparable & x, BinaryNode * & t );
41 void insert( Comparable && x, BinaryNode * & t );
42 void remove( const Comparable & x, BinaryNode * & t );
43 BinaryNode * findMin( BinaryNode *t ) const;
44 BinaryNode * findMax( BinaryNode *t ) const;
45 bool contains( const Comparable & x, BinaryNode *t ) const;
46 void makeEmpty( BinaryNode * & t );
47 void printTree( BinaryNode *t, ostream & out ) const;
48 BinaryNode * clone( BinaryNode *t ) const;
49 };
```

### Implementacion de un Arbol de Busqueda Binaria <br>

#### template \<typename Comparable> <br>

Para que el arbol de busqueda binario pueda funcionar, el tipo pasado mediante la *template* debe contar con el operador "***<***". Otra forma de manejar las comparaciones es mediante una funcion objeto, la cual al ser pasada como parametro pueda definir la forma en la que se deben comparar los datos de la *template*. 

>Un objeto de función, o functor, es cualquier tipo que implementa operator(). Este operador se conoce como el operador de llamada o a veces el operador de la aplicación. La biblioteca estándar de C++ usa objetos de función principalmente como criterios de ordenación para los contenedores y en algoritmos.
>
>Los objetos de función proporcionan dos ventajas principales en comparación con una llamada de función sencilla. La primera es que un objeto de función puede contener el estado. La segunda es que un objeto de función es un tipo y, por tanto, puede usarse como un parámetro de plantilla.<br>
>
>***Codigo de ejemplo***
>```c++
>class Functor
>{
>public:
>    int operator()(int a, int b)
>    {
>        return a < b;
>    }
>};
>
>int main()
>{
>    Functor f;
>    int a = 5;
>    int b = 7;
>    int ans = f(a, b);
>}
>```
>[2]	TylerMSFT, “Objetos de función en la biblioteca estándar de C++”, Microsoft.com. [En línea]. Disponible en: https://learn.microsoft.com/es-es/cpp/standard-library/function-objects-in-the-stl?view=msvc-170. [Consultado: 25-oct-2023].


#### *contains* <br>

Busca si un elemento existe. (regresa *verdadero*) o no (regresa *falso*) en un arbol. Esto mediante el uso de comparaciones y la estructura del arbol binario, donde el hijo izquierdo es menor que su padre y el derecho mayor.

```c++
public:

//Regresa verdadero si el elemento es encontrado
bool contains( const Comparable & x ) const{
    return contains( x, root );
}

/*
Método interno para buscar el elemento en un sub-arbol
x es el elemento a buscar
t es el nodo que funciona como raiz para el sub-arbol
*/
private: 
bool contains( const Comparable & x, BinaryNode *t ) const{
if( t == nullptr ){return false;} //Se ah pasado un nodo hoja, elemento no encontrado
else if( x < t->element ){return contains( x, t->left );} //El elemento x es menor al elemento de la raiz, se continuara buscando por el sub-arbol izquierdo
else if( t->element < x ){return contains( x, t->right );}//El elemento x es mayor al elemento de la raiz, se continuara buscando por el sub-arbol derecho
else{return true;} // Elemento encontrado
}
```



#### *findMin & findMax*

Estas rutinas buscan el menor y mayor elemento respectivamente, de un arbol y regresan un puntero hacia dicho nodo.<br>
Este metodo puede ser implementado tanto de manera recursiva como de manera no recursiva.

```c++
//Implementación recursiva con findMind

BinaryNode * findMin( BinaryNode *t ) const{
    if( t == nullptr ) {return nullptr;} //Si el arbol se encuentra vacio regresa un puntero nulo
    if( t->left == nullptr ){return t;} //Si el nodo no posee un hijo izquierdo, significa que habremos llegado al valor minimo
    return findMin( t->left );//Si aun se tiene un nodo hijo izquierdo se continua la busqueda desde dicho nodo llamando recursivamente esta funcion, una vez encontrado se regresa el nodo
}
```

```c++
//Implementacion NO recursiva con findMax

BinaryNode* findMax( BinaryNode *t ) const
{
    //Si el puntero no es nulo, se procede con la busqueda
    if( t != nullptr ){
        while( t->right != nullptr ) {t = t->right;} //Se movera por el nodo derecho hasta llegar al ultimo, siendo este el maximo
    }

    return t; //Se regresa un puntero al nodo encontrado
}
```

####  *insert*

La insercion es simple, primero, se realiza un *contains* para buscar si el elemento *X* a insertar existe o no en el arbol, si el elemento existe no se hace nada. Si no existe se inserta como hijo del ultimo nodo seguido en el camino del *contains*.<br>
Los duplicados pueden se manejados dejando un campo extra en el nodo para indicar la frecuencia de un elemento. Esto agrega mayor peso a los nodos y al arbol en general, pero es mejor que manejar duplicados.<br>  

```c++
//Insertar por referencia
void insert( const Comparable & x, BinaryNode *&t){
    if( t == nullptr ){t = new BinaryNode{ x, nullptr, nullptr };} //Si no encontramos un nodo vacio, insertamos el nodo en dicha posicion
    else if( x < t->element ){insert( x, t->left );} //Si el elemento X es menor al elemento del nodo lo insertamos como hijo izquierdo
    else if( t->element < x ){    insert( x, t->right );} //Si el elemento X es mayor al elemento del nodo lo insertamos como hijo derecho
    else; // Duplicado, no se hace nada
}

//Insertar por copia
void insert( Comparable && x, BinaryNode *&t){
    if( t == nullptr ) {t = new BinaryNode{ std::move( x ), nullptr, nullptr }; }//Si no encontramos un nodo vacio, insertamos el nodo en dicha posicion
    else if( x < t->element ){insert( std::move( x ), t->left );} //Si el elemento X es menor al elemento del nodo lo insertamos como hijo izquierdo
    else if( t->element < x ) {insert( std::move( x ), t->right );} //Si el elemento X es mayor al elemento del nodo lo insertamos como hijo derecho
    else; // Duplicado, no se hace nada
}
```

#### *remove*

Para eliminar un nodo, debemos tener varias consideraciones. <br>

* Si es un nodo hoja, el nodo puede ser elimiado inmediatamente.<br>
* Si el nodo tiene un solo hijo, el nodo sera borrado y su hijo pasara a tomar el lugar de su padre.<br>
* Si el nodo tiene 2 hijos, se usara la funcion findMin para encontrar el menor de los elementos, el cual tomara el lugar del elemento a borrar y su nodo original (un nodo hoja), sera borrado.<br>
* Si dentro del arbol se lleva un conteo de frecuencia de un elemento se bajara el numero de la frecuencia, si esta llega a 0, se reliza uno de los metodos de arribal.<br>
* *Lazy deletion*, se emplea cuando se prevee que el numero de eliminacion sea pequeno, el nodo se deja en el arbol y solamente se marca como *borrado*.<br>

```c++
void remove( const Comparable & x, BinaryNode *&t){

    //Inicia busqueda del elemento

    if( t == nullptr ){return;} // No se encontro el elemento, no se hace nada
    
    //Busqueda recursiva del elemento por el sub-arbol de izquierdo
    if( x < t->element ){remove( x, t->left );}
    
    //Busqueda recursiva del elemento por el sub-arbol de derecho
    else if( t->element < x ){remove( x, t->right );}

    //Una vez encontrado el elemento

    //Caso de 2 hijos
    else if( t->left != nullptr && t->right != nullptr ) {
        //Iguala el nodo actual al nodo menor del sub-arbol derecho
        t->element = findMin( t->right )->element;

        //Se busca el elemento menor del sub-arbol derecho y se elimina
        remove( t->element, t->right );
    }
    
    //Caso de 1 o 0 hijos
    else{
        //Se guarda el nodo a borrar
        BinaryNode *oldNode = t;

        //Si existe uno de los hijos se guarda en la posicion del nodo padre
        t = ( t->left != nullptr ) ? t->left : t->right;

        //Se borra el nodo
        delete oldNode;
    }
}
```
#### Destructor

Como en el resto de estructuras ADT, primero se vacia completamente la estructura y despues se destruye la estructura propiamente<br>

```c++
//Destructor
~BinarySearchTree(){
    makeEmpty();
}

//Metodo interno para vaciar el arbol
private:
void makeEmpty( BinaryNode * & t ){
    //Si el nodo actual no esta vacio se llama de forma recursiva el metodo para destruir sus posibles hijos

    if( t != nullptr ){
        makeEmpty( t->left ); //Se ejecuta el metodo en el sub-arbol izquierdo
        makeEmpty( t->right ); //Se ejecuta el metodo en el sub-arbol derecho
        delete t; //Se elimina el nodo t0
    }

    //Se convierte el nodo en un puntero nulo
    t = nullptr;
}
```

#### Copy constructor

```c++
//Constructor por copia
BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }{
    //Se clonan todos los elementos del arbol rhs al arbol lhs
    root = clone( rhs.root );
}

//Metodo interno para copiar un arbol o sub-arbol
BinaryNode * clone( BinaryNode *t ) const{
    if( t == nullptr ){return nullptr;} //Si el nodo es nulo, se termina la copia del sub-arbol
    else{return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };} //Si el nodo existe, se continuan copiando los sub-arboles de sus hijos    
}
```

## Arboles AVL

Un arbol AVL (Adelson-Velskii and Landis) es un arbol de busqueda bianria el cual cuenta con una condicion de blanace, este balance se asegura que la profundida del arbol es de $O(LogN)$, aunque en realidadm suele ser un poco mayor.<br>

Otra condicion de balance implica que cada nodo debe tener sub-arboles izquierdos y derechos de la misma altura. Con este principio los unicos arboles que pueden estar balanceados son arboles con $2^k - 1$ nodos. Por lo cual la condicon no puede ser tan rigida.<br>

En este sentido un arbol AVL es identico a un arbol de busqueda  binaria con la difere con que la diferencia de altura entre los nodos izquierdos y derechos debe ser  menor a 1. La altura de un arbol vacio es de -1.<br>

Todas las operaciones en un arbol AVL son posibles con un tiempo de $O(logN)$, excepto por la incercion y delecion.<br>
Para realizar una insercion, se necesita actualizar la informacion de balance de los nodos en el camino de regreso a la raiz, ya que de otra forma se podria eliminar la propiedad del arbol AVL.<br>

Para solucionar esto se puede realizar mediante una modificacion llamada *rotacion*. Esta afectara a los nodos que estan en el camino de insercion del nodo.<br>

La insercion puede ocurrir en uno de cuatro casos:<br>
* En el sub-arbol izquierdo del hijo izquierdo
* En el sub-arbol derecho del hijo izquierdo
* En el sub-arbol izquierdo del hijo derecho
* En el sub-arbol derecho del hijo derehco

<br>

Estos a su vez, se agrupan en 2 casos:<br>
* El primero enn el que la insercion ocurre en "exterior" (derecha-derecha, izquierda-izquierda), este se soluciona mediante una **rotacion simple**.
* El segundo es en el que la insercion ocurre en el "interior" (izquierda-derecha, derecha-izquierda), el cual se soluciona mediante una **rotacion doble**.

### Rotacion simple

Esta ocurre para solucionar una violacion al balance del arbol AVL en un nodo insertado en el sub-arbol izuiqerdo del hijo izquiero o el sub-arbol derecho del hijo derecho.<br>

La solucion consiste en los siguientes pasos: <br>

* Tomar el nodo raiz del sub-arbol donde ocurrio el desbalance
* Si el desbalance ocurrio en el sub-arbol derecho del hijo derecho:
    * Convertir el sub-arbol izquierdo del hijo derecho del nodo sub-raiz en el hijo derecho del nodo sub raiz
    * Convertir el hijo derecho del nodo sub-raiz en la nueva raiz
    * Convertir el nodo sub-raiz original en el hijo izquierdo de la nueva sub-raiz
* Si el desbalance ocurrio en el sub-arbol izquierdo del hijo izquierdo:
    * Convertir el sub-arbol derecho del hijo izquierdo del nodo sub-raiz en el hijo izquierdo del nodo sub raiz
    * Convertir el hijo izquierdo del nodo sub-raiz en la nueva raiz
    * Convertir el nodo sub-raiz original en el hijo derecho de la nueva sub-raiz

### Rotacion doble

Esta se realiza cuendo una se causa una violacion al balance AVl se realiza en el sub-arbol izquuierdo del hijo derecho o en el sub-arbol derecho del hijo izquierdo.<br>

Para solucionar esto, se encuentra el nodo donde ocurre el desbalance, este nodo sera *k1*, el siguiente nodo en el camino sera *k3* y el siguiente sera *k2*.<br>

Ahora realizamos lo siguiente:
* *k2* pasara a ser el nodo sub-raiz del sub-arbol a reordenar
* *k1* pasara a ser el hijo izquierdo de *k2*
* *k3* pasara a ser el hijo derecho de *k2*
* Si *k2* tenia hijos:
    * Su hijo izquierdo pasara a ser el hijo derecho de *k1*
    * Su hijo derecho pasara a ser el hijo izquierdo de *k3*

> ### Rotaciones *extra* (porque el libro solo dio ejemplo y no explicacion como o cuando)
> "Para conocer si un arbol AVL mantiene sus caracteristicas de equilibrio es necesario conocer el ***Factor de equilibrio*** de cada nodo involucrado en el camino de una insercion o delecion."
> "Para conocer este factor de equilibrio (***FE***),  se calcula: Profuindidad del sub-arbol derecho menos profundidad del sub-arbol izquierdo."
> "Un arbol AVL equilibrado tiene todos sus nodos con un factor de equilibrio de {-1,0,1}."
> "Una rotacion es una reestructuracion local de un sub-arbol para mantener la propiedad de equilibrio del arbol"
> "Tras una operacion de insercion.delecion se realiza un recalculo de las alturas de los nodos del camino, teniendo en cuenta la nueva altura de cada sub-arbol"
> "Para rebalancear un arbol se requiere de una rotacion, que puede ser simple o doble, ademas de en una direcccion, derecha o izquierda."
>  "Si el nodo desequilibrado es a la izquierda (FE < -1), y su hijo izquierdo tiene el mismo signo (-), se hace una rotacion simple a la derecha"
> "Si el nodo desequilibrado esta a la derecha y su hijo tiene el mismo signo (+), se hace una rotacion simple a la izquierda"
> "Si el nodo desequilibrado es a la izquierda (FE < -1), y su hijo izquierdo tiene el distinto signo (+), se hace una rotacion doble izquierda-derecha"
> "Si el nodo desequilibrado es a la derecha (FE>1) y su hijo tiene distinto signo (-) se realiza una rotacion doble derecha-izquierda"
>
>[3]	MrRocket, “Arbol Avl de insercion y eliminacion y ordenamiento”, 05-jul-2018. [En línea]. Disponible en: https://www.youtube.com/watch?v=UnhMzEaLDdw. [Consultado: 28-oct-2023].



# Opinion critica

Los arboles, son el siguiente paso de las listas y sus variaciones. <br>
En estos podemos encontrar una estructuracion mas compleja, ya que se puede considerar como listas con sub-listas, que pueden tener una cantidad infinita de sub-listas y por lo tanto de elementos.<br>

Esto puede llegar a ser beneficioso, sin embargo tambien puede ser caotico y complicado de ver y administras, ademas de la existencia de variaciones en la cantidad de nodos que puede llegar a tener un hijo, hace que se vuelva en una estructura complicada e ineficiente la cual se vuelve incapaz de competir con otras estructuras, como las listas, por ejemplo.<br>

Debido a esto se necesitan de controles extras para hecer mas ordenado y comprensible un arbol. Para resolver esta problematica entran los *Arboles de busqueda binaria* los cuales limitan la cantidad de hijos de cada nodo a 2 y les da un cierto orden, haciendo que los elementos de los hijos izquierdos sean menores que el nodo padre, mientras que los derechos sean mayores que el nodo padre. De esta forma, no solo se consigue tener un poco mas de orden en los datos, sino que generan una guia en caso de que se requiera hacer una busque en todos los elemento, sino que se se puede ir acercando mas a la posicion del elemento buscado gracias a esta jerarquia, mejorando los tiempos de las operaciones realizadas en el arbol.

Sin embargo, esto trae un nuevo problema, el desbalanceo del arbol, en el cual, si por ejemplo se inserta primero el elemento mayor y consecutivamente todos los elementos menores, se creeara un arbol el cual funcionalmente sera una lista. En solucion a esto se creo el *Arbol AVL*, el cual es un tipo de arbol de busqueda binaria el cual al realizar una operacion de insercion o de delecion se autobalancea, mediante rotaciones, haciendo asi que excepto las operaciones de insercion y delecion esten en complejidades de $O(logN)$, siendo una gran progresion con respecto a la complejidad lineal de las listas, demostando asi la eficiencia y el potencial que pueden llegar a tener lso arboles, en especial con grandes cantidades de datos.

# Opinion personal

Despues de haber pasado por un capitulo de repaso intenso, seguido de uno de tranquilidad por enteder el tema, llegan los arboles para bajar sus tiempos de complejidad pero aumentar la complejidad de su entendimiento. Aunque esta afirmacion solo es verdadera para los arboles AVL, ya que los arboles y arboles de busqueda binaria, no son tan complicados de entender, en especial con el conocimiento previo de listas, funcionamiento y bases logicas, por lo cual se sigue avanzando en este *arbol* de habilidades sobre las  estructuras de datos (Lo se el chiste es horrible pero me gustan las *dad jokes*).<br>
Pese a esto aun se siguen presentando retos, en especial con los conceptos unicos, como las rotaciones, las cuales demuestran que aun se puede mejorar y que se necesita un poco mas de informacion ademas de la proporcionada por el libro. En conclucion un buen capitulo y +1 en el arbol de habilidades, por suerte es +1 y no +2 que si no habia que rebalancear.



# Bibliografía

[1]	I. T. I. Gestión, U. De, y V.-D. De Informática, “Estructuras de Datos -Curso 02/03”, Uva.es. [En línea]. Disponible en: https://www.infor.uva.es/~cvaca/asigs/transp3.pdf. [Consultado: 23-oct-2023]. <br>
[2]	TylerMSFT, “Objetos de función en la biblioteca estándar de C++”, Microsoft.com. [En línea]. Disponible en: https://learn.microsoft.com/es-es/cpp/standard-library/function-objects-in-the-stl?view=msvc-170. [Consultado: 25-oct-2023]. <br>
[3]	MrRocket, “Arbol Avl de insercion y eliminacion y ordenamiento”, 05-jul-2018. [En línea]. Disponible en: https://www.youtube.com/watch?v=UnhMzEaLDdw. [Consultado: 28-oct-2023]. <br>
[4]	M. A. Weiss, Data Structures and Algorithm Analysis in C++, 4a ed. Upper Saddle River, NJ, Estados Unidos de América: Pearson, 2013.<br>

