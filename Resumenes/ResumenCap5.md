# Hashing

Lo idóneo para una tabla *hash* es que esta sea un arreglo de un tamaño fijo que contenga elementos. En estos elementos se guarda una llave, la cual sera empleada para la búsqueda en la tabla. Mientras que los elementos pueden contener mas información.<br>
El *tamaño de la tabla* es es una parte de la estructura de la tabla hash y no un simple numero. Normalmente la tabla tiene un tamaño de 0 a *tamaño de la tabla* - 1.<br>
Cada una de las llaves de la tabla es mapeada en un rango de 0 a *tamaño de la tabla* - 1. Este proceso se llama ***función hash***, la cual idealmente debe ser simple de procesar y de asegurarse que cada llave sea única y se encuentre en celdas diferentes. Aunque debido a que hay un numero finito de espacios en la tabla y una cantidad virtualmente infinita de claves, esto es imposible, por lo que se procura buscar una 1 que distribuya correctamente las llaves en toda la tabla.<br>

Esta es la idea general de una tabla hash, por lo que para hacer una, solo queda decidir el tamaño de la tabla, la función hash y que hacer en caso de que dos llaves den el mismo hash(resolución de colisiones).<br>

## Función Hash

Lo normal para una tabla hash es que la llave sea numérica, ya bien sea un numero propiamente o un *string* el cual mediante los valores de la tabla *ASCII* cada uno de sus caracteres se conviertan en un valor numérico.

Uno de los puntos clave al crear una función es hacer que el tamaño de la table sea un numero primo, para que asi esta tenga mayor dinamismo a la hora de usarse como paramento para obtener la llave asi como en el mapeo.

Existen infinitas funciones hash, pero para que estas sean eficientes lo recomendable es que sean fáciles de computar, que distribuya los datos de manera uniforme para evitar colisiones y facilitar su manejo. Una de las opciones mas comunes es tomar las letras del *string* y mediante una operación fija, como modulo, suma, multiplicación... obtener un valor, el problema con esto es que los idiomas no son aleatorios, y siguen patrones, por lo cual constantemente nos encontraremos con colisiones, ademas de que en caso de que no haya colisiones los valores no estarán distribuidos de manera uniforme.<br>

> Algunos ejemplos de funciones hash, sus pros y contras
>***Método de division***
>Obtiene el modulo de la llave entre el tamaño de la tabla
>*Pros* 
>Es bueno con cualquier tamaño de tabla
>Es rápido al solo realizar una operación
>*Contras*
>Colisiones frecuentes
>
>***Método de la media raíz cuadrada"
>Se obtiene la raíz cuadrada de la llave y se extraen los dígitos del medio
>*Pros*
>Buen desempeño
>No se depende de los últimos o primeros dígitos de la llave
>*Contras*
>El tamaño de la llave limita el método, al duplicar el numero de dígitos.
>Colisiones constantes
>
>***Método de multiplicación***
>Se escoge un valor n tal que 0 \< n \<1, se multiplica dicho valor n por la llave, se resta n/Llave, se multiplica por el tamaño de la tabla y se obtiene el *floor* del numero resultante.
>Funciona con cualquier calor, pero da mejores resultados si el tamaño de la tabla es una potencia de 2.
>*Contra*
>El proceso puede llegar a ser tardado, en especial si no se cumple con la condición de su pro.
>[2]	R. R. Follow, “Hash Functions and list/types of Hash functions”, GeeksforGeeks, 19-dic-2021. [En línea]. Disponible en: https://www.geeksforgeeks.org/hash-functions-and-list-types-of-hash-functions/. [Consultado: 13-nov-2023].


De cualquier manera, no existe la función hash perfecta, y por lo tanto quedara a decision del programador y de las necesidades particulares del proyecto para el cual se implemente.<br>

> *Template specialization*
>No es parte del tema pero se usa en uno de los códigos y me resulto interesante
> "La especialización de plantillas (*template specialization*), es una característica de las plantillas de C++..."
>"Esta nos permite que una 1 que recibe un parámetro plantilla actué de manera distinta con un cierto tipo de dato..."
>"Un ejemplo del uso de esta característica es con un algoritmo de ordenamiento, en el cual para *strings* queremos usar quick sort, mientras que para el resto de tipos usaremos burbuja..."
>
> [3]	“Template specialization in C++”, GeeksforGeeks, 20-nov-2013. [En línea]. Disponible en: https://www.geeksforgeeks.org/template-specialization-c/. [Consultado: 13-nov-2023]. 


## Colisiones 

Sin dejar de lado la función hash, lo mas importante en la tabla hash es el manejo de colisiones, ya que sin conocer los datos a almacenar es casi imposible evitar una colisión, y cuando una de estas ocurran se debe tener un plan eficiente para mantener la hash funcionando de forma optima. Para lo cual existen distintos métodos. 

### Encadenamiento separado

Consiste en mantener una tabla hash la cual contenga listas simples de elementos los cuales tengan la misma llave hash.<br>
Para realizar una inserción se hace la función hash, se búsqueda la lista correspondiente y se inserta el nuevo en el frente de la misma.<br>
Mientras que para una búsqueda, primero se realiza la búsqueda en la tabla hash para saber en que lista buscar y después se realiza una búsqueda en la lista. Para este 1 las llaves de la tabla hash asi como de la lista deben ser de tipos comparables, por lo cual deben contar con el operador != y ==.<br>
Para este método se pueden usar ademas de listas, arboles de búsqueda binaria e incluso otras tablas hash. Cualquiera de los elegidos se esperan que estos sean cortos para no complicar la estructura.<br>


El factor de carga (λ) es la proporción entre el numero de elementos en la tabla entre el tamaño de la tabla. El tamaño promedio de una lista es igual al factor de carga. Por lo que el tiempo necesario para buscar en una de estas estructuras es el tiempo constante de la tabla hash mas el tiempo lineal para buscar en una lista. Una búsqueda exitosa requiere que $1 + (λ/2)$ de los elementos sean buscados. Por lo que se espera que FC se aproxime a 1.<br>

La mayor desventaja de este tipo de hashing es el uso de otra estructura como listas, las cuales cuentan con tiempos lineales para su búsqueda y hacen que la tabla hash pierda su sentido.

### Sondeo lineal

El sonde lineal es una función de *i*, en la cual en caso de una colisión se busca secuencialmente una celda libre para guardar el hash. Por lo que si en una tabla el hash *x* ya esta ocupado se buscara en $x+1, x+2,x+3.....x+n$ hasta encontrar una celda libre para guardar el hash.<br>
Esta estrategia causa **agrupamientos primarios**, lo que significa que se formaran bloques en la tabla, lo que causara que se necesiten varios intentos antes de encontrar una celda vacía, ya que las celdas contiguas se van llenando.
En promedio el numero esperado de sondeos antes de una 1 y para una búsqueda fallida es de $ 1/2 (1 + 1/(1 − λ)^2) $, aproximadamente, mientras que para una búsqueda exitosa es de $2 (1 + 1/(1 − λ)) $.<br>

### Sondeo cuadrático  

Es un método de resolución de colisiones que elimina el problema del agrupamiento primario del sondeo lineal. La función para este donde es $f(i) = i^2$. La celda buscada sera la que se encuentre a i^2 posiciones de la celda donde primero se intento hacer por primera vez la inserción.<br>

Para este método, entre mas llena se encuentre la tabla, peor sera su rendimiento, siendo que si esta a mas de la mitad de su capacidad, no se puede garantizar que se encuentre una celda vacía, y si el 1 de la tabla no es un numero primo, esto ocurrirá incluso antes que esto.<br>

Por esto es necesario que el tamaño de la tabla sea un numero primo, ya que de lo contrario el numero de posiciones posibles se reduce.<br>

Debido a esto, el borrar un elemento en este tipo de sondeo, requiere que se haga mediante una eliminación *perezosa* (que de perezosa solo el nombre), para la cual, en cada una de las entradas de la tabla, ademas de la llave y su información, necesitaremos de un estado, que nos indique si la entrada esta activa, vacía o borrada, en donde si la casilla no esta activa, podrá ser reemplazada.

#### Tabla hash con sondeo cuadrático

```c++

//Interfaz tabla hash

template <typename HashedObj>
class HashTable{

public:

//Constructors explicito
explicit HashTable( int size = 101 ); 

//Métodos públicos
bool contains( const HashedObj & x ) const;
void makeEmpty( );
bool insert( const HashedObj & x );
bool insert( HashedObj && x );
bool remove( const HashedObj & x );
enum EntryType { ACTIVE, EMPTY, DELETED };

private:

//Estructura anidada que almacena la información
struct HashEntry{
HashedObj element;
EntryType info;
HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
: element{ e }, info{ i}{}
HashEntry( HashedObj && e, EntryType i = EMPTY )
: element{ std::move( e ) }, info{ i}{}
};

//Miembros privados
vector<HashEntry> array;
int currentSize;

//Métodos privados
bool isActive( int currentPos ) const; 
int findPos( const HashedObj & x ) const; 
void rehash( ); 
size_t myhash( const HashedObj & x ) const;

};
```

##### Inicializadores 

```c++
/*
Constructor explicito
Se inicia el tamano en el siguiente numero primo al tamano pasado como parámetro
    Si ningún numero es pasado se inicia en 101 
Se hace que los elementos de la tabla estén vacíos
*/
explicit HashTable( int size = 101 ) : array( nextPrime( size ) )
{ makeEmpty( ); }

//Hacer vacíos
void makeEmpty( ){
    currentSize = 0; //Se pone el tamano de la tabla como 0
    //Se hace que cada uno de los elementos tenga su info como "vació"
    for( auto & entry : array ){
        entry.info = EMPTY;
    } 
}
```

##### Buscar
```c++
bool contains( const HashedObj & x ) const { return isActive( findPos( x ) ); } //Regresa si un elemento x activo existe o no

int findPos( const HashedObj & x ) const{
    int offset = 1;
    int currentPos = myhash( x );
    
    //Se busca una posición que no este vacía y no contenga el elemento
    //Si lo contiene sale del ciclo, el elemento ya existe
    while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x ){
    
    currentPos += offset; // Se avanza desde la posición inicial mas el desfase
    offset += 2; //Se aumenta el desfase en 2
    
    //Si la posición es mayor al tamano del arreglo, se arregla retándole este
    if( currentPos >= array.size( ) ){
        currentPos -= array.size( );
    }
    }

    //Se regresa la posición encontrada.
    return currentPos;
}

bool isActive( int currentPos ) const { return array[ currentPos ].info == ACTIVE; }//Regresa si un elemento en la posición x esta o no activo
```

##### Insertar y eliminar

```c++
//Insertar
bool insert( const HashedObj & x ){

int currentPos = findPos( x );

//Si el elemento ya existe se regresa y no se hace nada
if( isActive( currentPos ) ){
   return false; 
}

//Guarda el elemento x en la posición encontrada
array[ currentPos ].element = x;
//Marca x como activo
array[ currentPos ].info = ACTIVE;

// Si el numero de elementos es mayor a la mitad del tamano de la tabla se hace un rehash
if( ++currentSize > array.size( )/2)
rehash( );
return true;
}

//Eliminar
bool remove( const HashedObj & x ){
int currentPos = findPos( x );
//Si el la posición del elemento x es diferente a activa regresa sin hacer nada mas
if( !isActive( currentPos ) ){
    return false;
}

//De lo contrario se pone la posición como eliminada y regresa
array[ currentPos ].info = DELETED;
return true;
}
```

### *Double hashing* 

En este método, al fallar el encontrar una celda en el primer hash, se realiza un segundo hash, en el cual se suele avanzar el resultado del segundo hash para buscar una celda libre.<br>

Para este método la función nunca debe de evaluar 0 y se debe asegurar que con el segundo hashing, todas las celdas puedan llegar a ser sondeadas.<br>

Para este método es importante que el tamano de la tabla sea un numero primo ya que de otra manera nos podemos quedar virtualmente sin posibles celdas para guardar el dato.<br>

Este método es interesante ya que se espera el mismo numero de sondeos que en una estrategia de resolución aleatoria, de cualquier manera el sondeo cuadrático es mejor, ya que no requiere de computar un segundo hash, lo que lo vuelve mas simple, rápido y practico.<br>

## Rehashing 

Si la tabla se empieza a llenar demasiado, sus operaciones empezaran a tomar mucho tiempo, y las inserciones pueden llegar a fallar con el sondeo cuadrático. Una solución para esto es construir otra tabla hash con un tamano igual al menor numero primo mayor al doble del tamano de la vieja tabla. Esta nueva tabla cuenta con su propia función hash, escanea toda la vieja tabla creando un nuevo valor hash y la inserta en la nueva tabla.

Esta operación es costosa ya que tiene un tiempo de $O(N)$, pero no es del todo mala, ya que para que se llamada deben haber ocurrido alrededor de $N/2$ inserciones antes del rehash, lo que hace que cada inserción tenga un tiempo constante.

Existen varias formas de implementar el rehashing en una resolución de sondeo cuadrático. <br>
Una de ellas seria en el momento en que la tabla supere la mitad de su capacidad, otro seria en el caso de que no se pueda realizar una inserción o bien cuando la tabla llegue a un factor de carga predeterminado.<br>



# Opinion critica

Las tablas hash son el siguiente paso hacia las operaciones con mejor tiempo, el tiempo constante. Pese a esta mejora que parecería  implicar mayor complejidad en otros aspectos no los tiene del todo, ya que una tabla hash es bastante directa. Necesitas una función para buscar, una para hacer un hash, una para resolver colisiones, una en para hacer rehash y otra para insertar y borrar. <br>
Si bien teóricamente una tabla hash es simple el problema de esta recae en su implementación, ya que para mantener este tiempo constante y evitar situaciones en las que no se puede insertar un elemento, se debe realizar un solido planteamiento de los algoritmos de hash y de resolución de colaciones. Ya que la verdadera eficiencia de las tablas hash recae en estos 2, en el contar con un buen algoritmo de hash que no genere continuamente colisiones, asi como un buen algoritmo gestor de colisiones cuando inevitablemente estas ocurran.<br>
Debido a esto el entendimiento de los procesos del *hashing* asi como un buen diseño son vitales, en especial ya que estos algoritmos no están tallados en piedra y se pueden modificar amplia y especialmente para cada una de las situaciones en la que se estén lo que da flexibilidad cuando se conoce los datos a trabajar y limitan y requieren de especial cuidado cuando no se conocen. 

# Opinion personal 

Las tablas hash son un tipo de estructura curiosa cuanto menos. Conceptualmente son las mas sencillas de entender e implementar, pero el problema de las mismas llega con su diseño, ya que como son de fáciles de entender son de fáciles de romper y hacerles perder su sentido (tiempos de operación constante). Por lo cual lo mas importante es tener una buena planeacion y conocimiento de los distintos algoritmos para la implementación, siendo asi que para esta estructura no solo tienes que escogerla como la estructura mas optima para la situación, implementarla y ya, si no que se tiene un nivel de planteamiento extra para hacer que funcione y no causar que esta llegue a explotar.<br>
En conclusion un tema corto siempre y cuando el algoritmo no llegue y explote todo.<br>
Y que vivan los números primos, psicópatas sin ley los cuales aquí sirven para siempre poder variar los movimientos durante las colisiones.

# Bibliografía



[1]	M. A. Weiss, Data Structures and Algorithm Analysis in C++, 4a ed. Upper Saddle River, NJ, Estados Unidos de América: Pearson, 2013.<br>
[2]	R. R. Follow, “Hash Functions and list/types of Hash functions”, GeeksforGeeks, 19-dic-2021. [En línea]. Disponible en: https://www.geeksforgeeks.org/hash-functions-and-list-types-of-hash-functions/. [Consultado: 13-nov-2023].<br>
[3]	“Template specialization in C++”, GeeksforGeeks, 20-nov-2013. [En línea]. Disponible en: https://www.geeksforgeeks.org/template-specialization-c/. [Consultado: 13-nov-2023].<br>
