# Algoritmos de ordenamiento 

Lo siguientes algoritmos operan mediante un ***comparison-based sorting***, por lo que se asume que los datos cuentan con los operadores "<" y ">" para asignar un orden consistente,los cuales, ademas del operador de asignación, son las únicas operaciones validas en los datos introducidos. También se asume que lo que se va a ordenar es un arreglo de posiciones con información comparable y ordenable, siendo ademas que se contiene un *N* numero de datos.<br>

## *Insertion sort*

Consiste en realizar N - 1 revisiones. Para cada revision *p* se asegura que las posiciones 0 a *p* se encuentren ordenadas, tomando esto como ventaja para ordenar el numero *p* de las siguiente revision.

### Complejidad 

```c++
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();

    // Recorremos el arreglo
    for (int i = 1; i < n; ++i) { //O(N)
        // Elemento del arreglo a ser ordenado
        int key = arr[i];

        // Movemos los elementos del arreglo que son mayores a nuestra llave
        int j = i - 1;
        while (j >= 0 && arr[j] > key) { //O(N)
            arr[j + 1] = arr[j];
            --j;
        }

        // Guardamos nuestra llave en la posición correcta
        arr[j + 1] = key;
    }
}
```
#### Temporal 

La complejidad temporal es de $O(N^2)$ debido a que cuenta con 2 ciclos lineales anidados. El primero de estos sirviendo para recorrer el arreglo y el segundo para ordenarlo.

#### Espacial

La complejidad espacial para este algoritmo es $O(1)$, lo que significa que es constante ya que ordena el arreglo en su espacio, por lo cual no requiere de memoria extra para almacenaro


### Ventajas

* Algoritmo simple
* Ordenamiento en el lugar, requiere poca memoria
* Desempeño decente en listas pequeñas

### Desventajas

* Debido a su tiempo cuadrático, tiene un peor desempeño con listas medianas y grandes de datos

### Utilidad

El algoritmo encuentra su lugar de mayor utilidad en listas de pocos elementos o en aquellas en las que se cuenten con una cantidad de memoria limitada por lo cual no se pueda permitir mantener tantas copias de los datos. O bien en una combinación de estas 2 situaciones.

>[2]	UdaySk, “Insertion sort algorithm”, Inprogrammer.com, 27-feb-2023. .



## *Shell sort*

Llamado asi debido a su inventor Donald Shell. Esta algoritmo fue uno de los primeros en romper la barrera del tiempo cuadrático, este funciona al comparar elementos lejanos e ir disminuyendo su lejanía conforme las revisiones hasta se realice una revision donde los elementos comparados sean adyacentes.<br>
Debido a esto, también se suele referir a este algoritmo como ***diminishing increment sort***.<br>


### Complejidad 
```c++
template <typename Comparable>
void shellsort( vector<Comparable> & a ){
//Determinamos el tamaño del paso
for( int gap = a.size( ) / 2; gap > 0; gap /= 2 ){ //O(log N)
        //Recorremos el arreglo
        for( int i = gap; i < a.size( ); ++i ){ //O(N)
            Comparable tmp = std::move( a[ i ] );
            
            //Revisamos seguir en los limites del arreglo y realizamos cambio si es necesario
            for( int j = i; j >= gap ; j -= gap ){ //O(N) 
                if(tmp < a[ j - gap ]){
                    a[ j ] = std::move( a[ j - gap ] );
                }
                
            }

            a[ j ] = std::move( tmp );
        }
    }
}
```

#### Temporal 

La complejidad de Shell sort es de $O(N^2)$. Esto debido a que cuenta con un par de ciclos anidados con complejidad lineal. El primer ciclo for (expresado en el código como $O(log N)$) puede llegar a ser engañoso, ya que realmente no aumenta la complejidad sino que solo condiciona el tamaño del paso que se hará al final cada ciclo for, sin embargo este hace que la complejidad promedio del algoritmo se acerque a $O( N log N^2)$ Ya puede llegar a reducir hasta la mitad el numero de comparaciones del segundo ciclo for, acercándolo a esta complejidad. 

#### Espacial

La complejidad espacial es de $O(1)$, ya que es un algoritmo de ordenamiento en lugar, lo que significa la cantidad de memoria adicional que necesita es independiente del numero de elementos a ordenar.

### Ventajas

* Tiene una eficiencia promedio ligeramente menor a la cuadrática. <br>
* No requiere mucha memoria memoria adicional y esta no incrementa con el numero de elementos.<br>

### Desventajas

* Mala optimizacion para el peor caso, mantiene un complejidad de $O(n^2)$.<br>
* No mantiene el orden de elementos con el mismo valor.<br>

### Utilidad

Util para situaciones en las que se busque ordenar una lista pequeña o mediana, o bien cuando se necesite hacer un ordenamiento en un sistema con recursos limitados. <br>
Tiene las misma utilidad que algoritmos como *insertion* o *bubble*, con la ventaja de tener en promedio una mejor tiempo usando el mismo espacio.

> [3]	“Shell Sort: Advantages and Disadvantages”, Shiksha.com. [En línea]. Disponible en: https://www.shiksha.com/online-courses/articles/shell-sort-advantages-and-disadvantages/. [Consultado: 22-nov-2023].


## *Heap sort*

Es un algoritmo basado en la estructura conocida como *Heap*, la cual es un arbol el cual esta lleno, excepto por su ultimo nivel, lo que hace que tenga entre $n^k$ y *n<sup>k+1</sup>*-1.<br>
Por lo que mediante la realizacion de N veces la operacion *deletemin* que elimina el menor elemento de la estructura. Obtenemos un tiempo de $O(N log N)$.<br>
Gracias a que contamos con la posibilidad de representar un *heap* como un arreglo, podemos realizar este ordenamiento con una complejidad espacial constante, al usar el espacio borrado del arreglo como el inicio del ordenamiento.<br>


### Complejidad 
```c++
template <typename Comparable>
void heapsort( vector<Comparable> & a ){
    
    //Construccion del heap
    for( int i = a.size( ) / 2 - 1; i >= 0; --i ){ //O(N)
        percDown( a, i, a.size( ) );
    } 
    for( int j = a.size( ) - 1; j > 0; --j ){ //O(N)
        std::swap( a[ 0 ], a[ j ] ); //Pasamos la raíz (que es el elemento mayor) a la ultima posición, ordenándolo
        percDown( a, 0, j ); //O(log N)
    }
}

inline int leftChild( int i ){ return 2 * i + 1;} //Regresa el indice del hijo izquierdo en el arreglo

template <typename Comparable>
void percDown( vector<Comparable> & a, int i, int n ){

    int child;
    Comparable tmp;//Variable que guarda la raíz

    //Buscamos el elemento mayor en le maxHeap
    for( tmp = std::move(a[ i ]); leftChild(i) < n; i = child ){ //O(log N)
        child = leftChild( i );
        //Comparamos cual de los dos hijos es el mayor
        if( child != n - 1 && a[ child ] < a[ child +1]){
            ++child;
        }
        //Pasamos el nodo mayor a su padre
        if( tmp < a[ child ] ){
            a[ i ] = std::move( a[ child ] );
        }
        else{
           break; 
        }
        
    }
    //Guardamos el dato en la posición mas lejana sin ordenar
    a[ i ] = std::move( tmp );
}
```

#### Temporal

La complejidad temporal del algoritmo es de $O(N log N)$. Ya que en el algoritmo encontramos un ciclo for, el cual tiene un complejidad de $O(N)$, el cual anidado tiene la función percDown, la cual cuenta con un for de complejidad lineal, la cual es bajada a $O(log N)$ debido a que solo recorre la mitad de los elementos del arreglo, por lo que tenemos $O(N) * O(log N) = O(N log N)$<br>

#### Espacial

La complejidad de *HeapSort* es constante $O(1)$, ya que con la técnica adecuada el espacio de memoria adicional que este requiere es constante e independiente del numero de datos que se ingresen.

### Ventajas

* Tiempo asegurado de $O(N log N)$. <br>
* Uso de memoria constante. <br>
* Ordenamiento estable, al mantener el orden relativo de los elementos duplicados.<br>

### Desventajas

* No es adaptativo, por lo que incluso con arreglos parcialmente ordenados tarda lo mismo que con completamente desordenado.

### Utilidad

* Ordenar grandes cantidades de datos, con uso de poca memoria<br>
* Ordenamiento externo<br>
* Algoritmos de grados como Dijkstra's.<br>

> [4]	H. Yadav, “Heap Sort in data structure”, PrepBytes Blog, 13-feb-2023. [En línea]. Disponible en: https://www.prepbytes.com/blog/heap/heap-sort-in-data-structure/. [Consultado: 22-nov-2023].


## *Mergesort* 

Este algoritmo se fundamenta en unir 2 listas ordenadas en una tercera, debido a que ambas listas están ordenadas, esta operación puede realizarse en una única revision. <br>
La estructura básica consiste en tomar 2 arreglos ordenados A y B, y un tercer arreglo de salida C y tres contadores Actr, Bctr, Cctr, que inician en el respectivo inicio de sus arreglos, después se comparan Actr y Bctr, el menor de los dos se coloca en Cctr, después se avanza el contador de la lista con el numero menor y el contador de C.<br>

### Complejidad 

```c++
//Algoritmo que maneja el ordenamiento
template <typename Comparable>
void mergeSort( vector<Comparable> & a ){

vector<Comparable> tmpArray( a.size( ) ); //O(N)

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

//Algoritmo recursivo que 
template <typename Comparable>
void mergeSort( vector<Comparable> & a, vector<Comparable> & tmpArray, int left, int right ){
    if( left < right ){
        //Aplicación del concepto divide y vencerás, al dividir el arreglo en 2
        //Esto nos acerca al tiempo logarítmico
        int center = ( left + right ) / 2; 
        mergeSort( a, tmpArray, left, center );
        mergeSort( a, tmpArray, center + 1, right );
        merge( a, tmpArray, left, center + 1, right );
    }
}

template <typename Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,int leftPos, int rightPos, int rightEnd){
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Se unen el arreglo izquierdo y derecho mientras no se haya terminado ninguno de los 2
    while( leftPos <= leftEnd && rightPos <= rightEnd ){//O(N)
        
        if( a[ leftPos ] <= a[ rightPos ] ){
            tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
        }
        
        else {
            tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );
        }
    }

    //Se copia el resto del arreglo izquierdo si existe
    while( leftPos <= leftEnd ){//O(N)
        tmpArray[ tmpPos++ ] = std::move( a[ leftPos++ ] );
    }

    // Se copia el resto del arreglo derecho si existe
    while( rightPos <= rightEnd ){//O(N)
        tmpArray[ tmpPos++ ] = std::move( a[ rightPos++ ] );
    }

    // Se copia de regreso el arreglo temporal al original
    for( int i = 0; i < numElements; ++i, --rightEnd ){ //O(N)
        a[ rightEnd ] = std::move( tmpArray[ rightEnd ] );
    }
    
}
```

#### Temporal 

La complejidad de *MergeSort* es $O(log N)$. Esto pese a que cuenta unicamente con ciclos de complejidad $O(N)$, ya que si bien estos ciclos son lineales, nos acercamos mas a un comportamiento linearítmico gracias a que todos los elementos son divididos hasta llegar a arreglos individuales, los cuales son unidos con la función merge. Siendo asi que la division de elementos causa un tiempo logarítmico que aumenta a linearítmico debido a la union.

#### Espacial

La complejidad espacial es de $O(N)$ debido a que se requiere espacio adicional de N elementos durante cada nivel de recursion, por lo que esa es la complejidad.

#### Ventajas

* Se tiene garantizado un tiempo de $O(n log n)$ para todos los casos
* Eficiente para grandes conjuntos de datos

### Desventajas

* Requiere una cantidad extra de memoria de tamaño $O(N)$
* No es adaptable, por lo cual si el arreglo esta casi completamente ordenado tardara lo mismo que si esta completamente desordenado
* Ineficiente para grupos pequeños de datos

### Utilidad

Cuando se busca un método de ordenamiento que mantenga un equilibrio entre eficiencia temporal y espacial, en el cual se ingresen grandes cantidades de datos y se tengan recursos de memoria suficientes.<br>
En ocasiones en las que se tenga cierta certeza de que los datos estarán mayoritariamente desordenados, ya que si están parcialmente ordenados esto no importara y tomara el mismo tiempo que si estuvieran completamente desordenados.<br>
Este algoritmo también es recomendable en lenguajes los cuales mover elementos sea eficiente y realizar comparaciones no lo sea, mientras que no es recomendable en lenguajes donde las comparaciones estén optimizadas pero el movimiento de elementos no. Esto debido a que es el método con menor cantidad de comparaciones, pero con mayor cantidad de movimientos.

>[5]	“Merge sort, advantages and disadvantages”, Getrevising.co.uk. [En línea]. Disponible en: https://getrevising.co.uk/grids/merge-sort-advantages-and-disadvantages. [Consultado: 22-nov-2023].


## *Quicksort*

Históricamente uno de los algoritmos de ordenamiento genéricos mas rápidos. Con un tiempo promedio de $O(N log N), aunque tiene un peor caso de $O(N^2)$.<br>
Este algoritmo esta basado en el concepto de divide y vencerás.<br>
El algoritmo consiste en tomar arbitrariamente un pivote, enviarlo al final de la lista para quitarlo del camino y formar 3 grupos, elementos mayores, elementos menores y elementos iguales, posteriormente seguir ordenando de manera recursiva cada uno de los grupos, y posteriormente concatenados.<br>
Existen distintas estrategias para elegir un pivote, entre ellas nos encontramos: <br>
* Tomar el primer elemento de la lista, lo cual es bueno siempre y cuando la lista sea completamente aleatoria, ya que esi es preordenada, la particion sera mala.<br>
* Elegir un pivote aleatoreo. <br>
* Tomar el elemento medio de la lista.<br>
* La mediana de la lista, este metodo pese a ser la mejor eleccion, es tardado de hacer, por lo que se suele implementar tomando 3 numeros aleatorios y obteniendo su media. <br>

### Complejidad 
```c++
template <typename Comparable>
void SORT( vector<Comparable> & items ){
    //Mientras el arreglo contenga mas de 1 elemento
    if( items.size( ) > 1 ){
        //Creamos vectores auxiliares para el grupo mayor, menor o igual que el pivote
        //O(log N)
        vector<Comparable> smaller;
        vector<Comparable> same;
        vector<Comparable> larger;
    int chosenItem = items[ items.size( ) / 2 ]; //Elegimos el pivote
    
    //Llenamos los vectores auxiliares
    for( Comparable & i : items ){// O(N)
        if( i < chosenItem ){
                smaller.push_back( std::move( i ) );
        }
        else if( chosenItem < i ){
                larger.push_back( std::move( i ) );
        }
        else{
            same.push_back( std::move( i ) );
        }
    }

    //Ordenamos recursivamente el vector menor y mayor
    SORT( smaller ); //O(N)
    SORT( larger );  //O(N)

    std::move( begin( smaller ), end( smaller ), begin( items ) ); //Concatenamos el grupo menor en el inicio del vector
    std::move( begin( same ), end( same ), begin( items ) + smaller.size( ) ); //Concatenamos el grupo igual después del menor
    std::move( begin( larger ), end( larger ), end( items ) - larger.size( ) );//Concatenamos el grupo mayor después del igual
    }
}
```
#### Temporal

La complejidad temporal es $O(N^2)$, esto ya que realizamos la operación recursiva de SORT hasta N veces por lo que obtenemos que la complejidad es $O(N) * O(N) = O(N^2)$. Sin embargo, las operaciones recursivas tienen en promedio una complejidad de $O(N/2)$ debido al principio de divide y vencerás que emplean, por lo que el tiempo promedio es de $O(N log N)$.<br>

#### Espacial

EL algoritmo durante el proceso de creación de los sub arreglos menor y mayor requiere un espacio adicional de $O(log N)$ ya que estos almacenan aproximadamente la mitad de datos del arreglo anterior, por lo que este es su complejidad espacial.

### Ventajas

* Algoritmo eficiente en grandes cantidades de datos.<br>
* Requiere una baja cantidad de memoria $O(log N)$.<br>

### Desventajas

* Peor caso temporal de $O(N^2)$
* Mala eficiencia en grupos pequeños de datos.<br>
* No preserva las posiciones relativas de elementos con el mismo valor llave.<br>

### Utilidad

Ordenar grandes cantidades de datos en situaciones en las que no se dispone de una gran cantidad de memoria.<br>

>[6]	“QuickSort - data structure and algorithm tutorials”, GeeksforGeeks, 07-ene-2014. [En línea]. Disponible en: https://www.geeksforgeeks.org/quick-sort/. [Consultado: 22-nov-2023].


## *Bucket sort*

Para que el *bucket sort* funcione se debe considerar información adicional, la entrada de datos debe construir unicamente de enteros positivos menores a M. <br>
Si se cumplen estas condiciones el algoritmo es el siguiente: Crear un arreglo de tamano M, donde todos los valores se inician en 0, cuando el primer elemento de la entrada se lee se aumente su valor en el arreglo, al final se imprime los valores mayores a 0, obteniendo asi una representación de la lista ordenada.

### Complejidad 

```c++
void bucketSort(std::vector<float>& arr) {
    int n = arr.size();

    // Creamos la matriz de cubetas con el tamaño del arreglo
    std::vector<std::vector<float>> buckets(n);

    // Colocamos los elementos en las cubetas
    for (int i = 0; i < n; ++i) {//O(N)
        int bucketIndex = n * arr[i];
        buckets[bucketIndex].push_back(arr[i]);
    }

    // Ordenamos las cubetas con un método distinto (insertion en este ejemplo)
    for (int i = 0; i < n; ++i) { //O(N)
        std::sort(buckets[i].begin(), buckets[i].end());
    }

    // Unimos las cubetas en el arreglo ordenado
    int index = 0;
    for (int i = 0; i < n; ++i) { //O(N)
        for (float element : buckets[i]) { //O(N^2)
            arr[index++] = element;
        }
    }
}
```

#### Temporal 

Tiene una complejidad de $O(M+N)$ donde M elemento de mayor valor y N el numero de elementos, siendo asi que N<=M, por lo que en el peor delos casos tenemos que M=N, por lo que el peor caso es de $O(N^2)$.<br>

#### Espacial

Tiene una complejidad de $O(M)$ al necesitar un arreglo del 

### Ventajas

* Eficiente para grupos de datos reducidos

### Desventajas

* Tiempo de ejecución cuadrático. <br>
* Consumo de recursos lineal. <br>
* Necesidad de estructuras para mantener orden en las cubetas. <br>

### Utilidad

Solo es util para ordenar pequeñas cantidades de números enteros, los cuales se saben que no tendrán valores muy altos. Un ejemplo de e sto puede ser ordenar un conjunto de 10 edades. <br>

>[7]	“Bucket sort - data structures and algorithms tutorials”, GeeksforGeeks, 26-abr-2014. [En línea]. Disponible en: https://www.geeksforgeeks.org/bucket-sort-2/. [Consultado: 22-nov-2023].


## *Radix sort*

Es un algoritmo que consiste en realizar un *bucket sort* varias veces, primero se realiza un *bucket sort* con el primer dígito importante, después se realiza una segunda pasada con el segundo dígito mas importante y asi has ordenar el arreglo. El ordenamiento es estable, por lo cual si dos números caen en la misma cubeta el orden de estos se mantendrá. En este ordenamiento los números estarán ordenados hasta el dígito k, siendo k igual numero de pases que se hayan hecho.<br>

### Complejidad 

```c++
void radixSortA( vector<string> & arr, int stringLen ){
    const int BUCKETS = 256;

    //Estructura matriz para guardar cadenas que inician con cada carácter de la tabla ASCII
    vector<vector<string>> buckets( BUCKETS ); //O(N+K)

    for( int pos = stringLen - 1; pos >= 0; --pos ){//O(K)
        
        for( string & s : arr ){//O(N)
            buckets[ s[ pos ] ].push_back( std::move( s ) );
        }

        int idx = 0;
        
        for( auto & thisBucket : buckets ){//O(N)
            for( string & s : thisBucket ){
                arr[ idx++ ] = std::move( s );
            }
            
            thisBucket.clear( );
        }
    }
}
```
#### Temporal

La complejidad temporal es de $O(NK)$ ya que tendremos que ordenar K veces los N elemento, siendo K

#### Espacial

La complejidad espacial es de $O(N+K)$ ya que se necesitan N cubetas de tamano K para poder guardar temporalmente los elementos hasta que sean reordenados en su espacio de memoria original

### Ventajas

* Complejidad temporal lineal.<br>
* Mantiene el orden de l.os elementos con el mismo valor llave.<br>
* Eficiente para números y *strings*.<br>

### Desventajas

* No es eficiente con tipos de datos que no pudan ser facilmente mapeados en numeros pequenos de digitos (cubetas)<br>
* Requiere una alta capacidad de memoria.<br>
* Funciona mejor con datos que pueden ser ordenados con un solo ordenar una parte de sus digitos.<br>
* No funciona con conjuntos pequenos de datos que tengan cubetas unicas.<br>

### Utilidad

Ordenar *strings* con un tiempo lineal. Ordenar tipos de datos compuestos, en los cuales se requiera ordenar primero un sub-valor *a*, después uno *b*, *c*...<br>

>[8]	“Applications, advantages and disadvantages of Radix sort”, GeeksforGeeks, 07-jun-2023. [En línea]. Disponible en: https://www.geeksforgeeks.org/applications-advantages-and-disadvantages-of-radix-sort/. [Consultado: 22-nov-2023].


## Métodos de ordenamiento externo

Los métodos anteriores requieren un cantidad de datos que puedan ser almacenados en la memoria principal, sin embargo hay aplicaciones en las que esto no es posible, por lo cual requerimos de algoritmos que trabajen en la memoria externa y puedan manejar cantidades muy grandes de datos.

EL método escogido para estas situaciones es una variación del *merge sort* en el cual se emplea la mayor capacidad de las memorias estables para realizar el ordenamiento de los sub arreglos para posteriormente unirlos en un tercer arreglo ordenado. Debido al mayor espacio de memoria disponible se puede hacer un *merge* multiple en el cual se unen una *k* de sub-arreglos a la vez.<br>

Otro de los métodos escogidos es una combinación entre *heap sort* y *selection sort* llamado como *replacement selection*, en el cual los elementos son puestos en una cola de prioridad, el reemplazo en este proceso se logra mediante el método de *delete min* el cual produce la salida del elemento menor y permite guardar otro en su lugar de memoria.<br>

La combinación de estas dos métodos nos permite realizar un ordenamiento externo con eficiencia, usando primeramente el *replacement selection* para pre-ordenar los datos y ordenarlos y permitir que sean eficientemente ordenados mediante el uso de un *merge sort* multiple.<br>


# *BIG-O cheatsheet*

<img src ="https://www.bigocheatsheet.com/img/big-o-cheat-sheet-poster.png" alt = "Big-O Cheatsheet" height = "1000px" width = "auto">


>[9]	“Know thy complexities!”, Bigocheatsheet.com. [En línea]. Disponible en: https://www.bigocheatsheet.com/. [Consultado: 22-nov-2023].


# Opinion critica 

Los métodos de ordenamiento son algo vital para poder combatir el caos natural de las cosas, por desgracia este no siempre es igual, por lo cual tenemos que adaptarnos a la situación y los recursos de los que dispongamos. Debido a esto es importante conocer los distintos algoritmos de ordenamiento, en especial su complejidad espacial y temporal. Conociendo estos y los recursos de los que disponemos, podemos tomar una edición informada y asi escoger el algoritmo que mas se adapta a nuestras necesidades, sin casarnos con un algoritmo y emplearlo solo por gusto personal, sino que emplearlo debido a que es el que mejor se adapta a nuestra especifica situación y asi obtener la mayor eficiencia de nuestro proceso.<br>

# Opinion personal

Los algoritmos de ordenamiento son una clara prueba de que lo mas importante no es el aprenderse los mas mínimos detalles y memorizar linea por linea lo que se va hacer, sino que lo mas importante es el entender que es lo que se esta haciendo y aun mas importante el porque se esta haciendo. En este particular caso, no es muy util el saberse de memoria la implementación del algoritmo, sino que mas bien es vital el entender como funcionan, para comprender nuestra situación y poder resolverla de la mejor manera posible. Esto a su vez me parece lo mas importante que nos diferencia de las computadoras, tenemos la capacidad de el analizar el que, como y el cuando, y no solo arrogar toda la información que nos pidan solo  porque nos lo pidieron. <br>

# Bibliografía  

[1]	M. A. Weiss, Data Structures and Algorithm Analysis in C++, 4a ed. Upper Saddle River, NJ, Estados Unidos de América: Pearson, 2013.
[2]	UdaySk, “Insertion sort algorithm”, Inprogrammer.com, 27-feb-2023. .
[3]	“Shell Sort: Advantages and Disadvantages”, Shiksha.com. [En línea]. Disponible en: https://www.shiksha.com/online-courses/articles/shell-sort-advantages-and-disadvantages/. [Consultado: 22-nov-2023].
[4]	H. Yadav, “Heap Sort in data structure”, PrepBytes Blog, 13-feb-2023. [En línea]. Disponible en: https://www.prepbytes.com/blog/heap/heap-sort-in-data-structure/. [Consultado: 22-nov-2023].
[5]	“Merge sort, advantages and disadvantages”, Getrevising.co.uk. [En línea]. Disponible en: https://getrevising.co.uk/grids/merge-sort-advantages-and-disadvantages. [Consultado: 22-nov-2023].
[6]	“QuickSort - data structure and algorithm tutorials”, GeeksforGeeks, 07-ene-2014. [En línea]. Disponible en: https://www.geeksforgeeks.org/quick-sort/. [Consultado: 22-nov-2023].
[7]	“Bucket sort - data structures and algorithms tutorials”, GeeksforGeeks, 26-abr-2014. [En línea]. Disponible en: https://www.geeksforgeeks.org/bucket-sort-2/. [Consultado: 22-nov-2023].
[8]	“Applications, advantages and disadvantages of Radix sort”, GeeksforGeeks, 07-jun-2023. [En línea]. Disponible en: https://www.geeksforgeeks.org/applications-advantages-and-disadvantages-of-radix-sort/. [Consultado: 22-nov-2023].
[9]	“Know thy complexities!”, Bigocheatsheet.com. [En línea]. Disponible en: https://www.bigocheatsheet.com/. [Consultado: 22-nov-2023].




