# Clase SLList <br>

La clase SLList es una plantilla de tipo ADT la cual acepta cualquier tipo de dato y sirve para mantener una estructura de datos ordenada con multiples miembros.<br>
Este contenedor es de tipo lista por lo cual podremos expulsar miembros al principio y agregar otros al final.<br>
Asi mismo contamos con la opción de vaciar completamente la lista.<br>
Dentro de esta lista ademas contamos con los nodos centinelas, cabeza y cola para marcar el inicio y el final de la lista.<br>
En esta clase ademas encontramos métodos para imprimir toda la lista, inicializara, obtener su tamaño, si esta o no vacía asi como la implementación de constructores y destructores.<br>

Para esta clase ademas necesitaremos una clase anidada y una estructura anidada.<br>

## Nodo <br>

Los nodos son la estructura anidada que encontramos dentro de esta clase<br>
Esta se encarga de la organización de los miembros de la lista. Esto mediante una variable de tipo *Objeto* la cual se convertirá en el tipo pasado al crear la lista, y guardar la información correspondiente del objeto<br>
Junto a esta encontramos el puntero de tipo *nodo* el cual hace referencia al siguiente miembro en la lista y nos ayuda a mantener todos estos conectados.<br>

## Iterador <br>

Esta es la clase anidada de la lista.<br>
Esta clase es la encargada de recorrer los miembros de la lista, esto con el fin de ayudar a las funciones de la lista, ya bien sea para encontrando, insertando o eliminando un nuevo elemento.<br>