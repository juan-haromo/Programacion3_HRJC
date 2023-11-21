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

### Utilidad

Util para situaciones en las que se busque ordenar una lista pequeña o mediana, o bien cuando se necesite hacer un ordenamiento en un sistema con recursos limitados. <br>
Tiene las misma utilidad que algoritmos como *insertion* o *bubble*, con la ventaja de tener en promedio una mejor tiempo usando el mismo espacio.

## *Heap sort*

### Complejidad temporal y espacial

### Ventajas

### Desventajas

### Utilidad

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

### Utilidad

Cuando se busca un método de ordenamiento que mantenga un equilibrio entre eficiencia temporal y espacial, en el cual se ingresen grandes cantidades de datos y se tengan recursos de memoria suficientes.<br>
En ocasiones en las que se tenga cierta certeza de que los datos estarán mayoritariamente desordenados,. ya que si están parcialmente ordenados esto no importara y tomara el mismo tiempo que si estuvieran completamente desordenados.<br>
Este algoritmo también es recomendable en lenguajes los cuales mover elementos sea eficiente y realizar comparaciones no lo sea, mientras que no es recomendable en lenguajes donde las comparaciones estén optimizadas pero el movimiento de elementos no. Esto debido a que es el método con menor cantidad de comparaciones, pero con mayor cantidad de movimientos.

## *Quicksort*

Historicamente uno de los algoritmos de ordenamiento generecos mas rapidos. Con un tiempo promedio de $O(N log N)

### Complejidad temporal y espacial

### Ventajas

### Desventajas

### Utilidad

## *Bucket sort*

### Complejidad temporal y espacial

### Ventajas

### Desventajas

### Utilidad

## *Radix sort*

### Complejidad temporal y espacial

### Ventajas

### Desventajas

### Utilidad

## Métodos de ordenamiento externo


# *BIG-O cheatsheet*

<img src ="https://www.bigocheatsheet.com/img/big-o-cheat-sheet-poster.png" alt = "Big-O Cheatsheet" height = "1000px" width = "auto">

# Opinion critica 

# Opinion personal

# Bibliografia 




