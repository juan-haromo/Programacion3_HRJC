# Algoritmo de Dijkstra

Este algoritmo cumple la función de encontrar el camino mas corto de un nodo al resto de nodos. Se realiza en grafos dirigidos y con peso en sus aristas.<br>

Para este algoritmo se necesita mantener una lista, la cual guarda la información del nodo, el peso que se tiene para llegar a dicho nodo (por defecto marcado como infinito para que asi cualquier peso inicial sea menor) y el nodo que se tiene que seguir para seguir dicho camino. <br>

El algoritmo funciona de la siguiente forma:<br>
1. Se inicia la lista, agregando todos los nodos del grafo y se pone su peso como infinito y su ruta como 0 o nula.<br>
2. El nodo inicial se le coloca un peso de ruta de 0 y una ruta nula (al ser ese el nodo inicial).<br>
3. Se coloca los nodos adyacentes al nodo actual en una cola.<br>
4. Se hace un *dequeue* y se analiza dicho elemento.<br>
5. Se calcula el peso del camino, el cual es el peso de la ruta + el peso para llegar a dicho nodo.<br>
6. Se compara dicho peso con el peso de ruta guardado para dicho nodo<br>
    6.1 Si el peso nuevo es mayor al anterior no se hace nada y el elemento queda fuera de la cola<br>
    6.2 Si el peso nuevo es menor que el anterior, este se actualiza asi como el nodo desde el cual se llega par dicho peso, posteriormente se agregan sus nodos adyacentes par volver a calcular su peso e intentar encontrar una mejor ruta.<br>
7. Se repiten el proceso desde el paso 3 hasta que la cola quede vacía.<br>

Una vez realizado este proceso y manteniendo la tabla que contiene los caminos, se pueden imprimir estos tomando el nodo destino y siguiendo desde allí recursivamente su ruta del nodo anterior hasta llegar al nodo inicial.<br>
>[2]	Universitat Politècnica de València-UPV, “S3.4- Algoritmo de Dijkstra | | UPV”, 29-ene-2013. [En línea]. Disponible en: https://www.youtube.com/watch?v=eLFEIxDEphA. [Consultado: 30-nov-2023]. <br>
# Algoritmo de Prim

Este algoritmo es una forma de calcular un *árbol de sondeo mínimo* .<br>

Este consiste en iniciar tomando arbitrariamente un nodo "v1" y posteriormente seleccionar una arista (*v,w*), en la cual *v* sea parte del árbol y *w* no lo sea, de menor peso y se agrega al árbol con su correspondiente vértice, se realiza este proceso hasta que no quede ningún nodo accesible.<br>


Para realizar este algoritmo se mantiene una tabla similar a la del algoritmo de Dijkstra, en la cual necesitamos tener una todos los nodos, con un peso de camino infinito y camino nulo inicial, ademas de necesitar una variable extra para indicar si el nodo forma o no parte del árbol. Posteriormente se toma en nodo inicial *v1*, se marca como conocido y se agrega sus nodos adyacentes con peso y ruta. Posteriormente, de los nodos que no forman parte del árbol se busca el que tenga un menor peso en su camino y se agrega al árbol. Se repite este proceso hasta que no quede ningún nodo accesible.<br>
>[3]	M. Sambol, “Prim’s algorithm in 2 minutes”, 28-oct-2012. [En línea]. Disponible en: https://www.youtube.com/watch?v=cplfcGZmX7I. [Consultado: 30-nov-2023].<br>

# Bibliografía

[1]	M. A. Weiss, Data Structures and Algorithm Analysis in C++, 4a ed. Upper Saddle River, NJ, Estados Unidos de América: Pearson, 2013.
[2]	Universitat Politècnica de València-UPV, “S3.4- Algoritmo de Dijkstra | | UPV”, 29-ene-2013. [En línea]. Disponible en: https://www.youtube.com/watch?v=eLFEIxDEphA. [Consultado: 30-nov-2023].
[3]	M. Sambol, “Prim’s algorithm in 2 minutes”, 28-oct-2012. [En línea]. Disponible en: https://www.youtube.com/watch?v=cplfcGZmX7I. [Consultado: 30-nov-2023].
