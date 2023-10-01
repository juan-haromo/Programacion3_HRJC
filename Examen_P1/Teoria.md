# Examen1

Responde a las siguientes preguntas


## Parte 1.1

i. ¿Qué es un Rvalor y un Lvalor?
Son dos clasificaciones de datos en programación la diferencia siendo que los r valores son constantes y temporales mientras que los l valores no son temporales y son r valores asignados.

ii. ¿Porqué es necesario que una clase tenga constructores y operadores por
copia y por referencia?
Porque se necesita una manera de accesar ambos el dato original y la ubicación en donde se encuentra

iii. ¿Qué función desarrollan los :: en la implementación de la clase?
Hacen que a lo que refiere solo funcione dentro de la clase, mientras que : es global

iv. ¿Cómo se le denomina a cuando una clase posee un operador puede
tener múltiples implementaciones dependiendo de los argumentos que
este reciba?
Sobrecarga de tipo de dato

v. ¿Cúal es la funcion del archivo .h ?
El archivo .h o header sirve para asignar variables y parámetros de una clase

## Parte 2

### Complejidad Temporal
Calcular la complejidad temporal en Big(O) Notation del siguiente algoritmo:
```c++
#include <iostream>
int algoritmo1(int n) {
int resultado = 0;
for (int i = 0; i < n; i++) {
resultado += i; // Operación simple O(1)
}
for (int i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
resultado += i * j; // Operación simple O(1)
}
}
return resultado;
}
int main() {
int n;
std::cout << "Ingrese el valor de n: ";
std::cin >> n;

int resultado = algoritmo1(n);
std::cout << "Resultado: " << resultado << std::endl;
return 0;
}
```
$O(n^2)$