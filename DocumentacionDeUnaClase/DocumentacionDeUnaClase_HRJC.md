# IntCell.h Documentation

## Constructor por defecto
```c++
//Interfaz
explicit IntCell(int newValue = 0);
//Implementación
IntCell::IntCell(int newValue) : storedValue(newValue) {}
```
Puede aceptar un parámetro que sera guardado en la variable storedValue.<br>
Si no se proporcionan ningún parámetro, el valor por defecto es 0.<br>

## Constructor por copia
```c++
//Interfaz
IntCell(const IntCell &rhs);
//Implementación
IntCell::IntCell(const IntCell &rhs) : storedValue(rhs.storedValue) {}
```
En caso de crear una copia de esta clase, la variable storedValue del rhs, sera guardada en el storedValue del lhs.<br>

## Constructor de movimiento
```c++
//Interfaz
IntCell(IntCell &&rhs) noexcept;
//Implementación
IntCell::IntCell(IntCell &&rhs) noexcept : storedValue(rhs.storedValue) {
    rhs.storedValue = 0;
}
```
Toma el storedValue del rhs, lo pasa al storedValue del lhs.<br>
Regresa el valor de de storedValue del rhs a defecto, en este caso 0.<br>

## Operador = (Misma clase)
```c++
//Interfaz
IntCell &operator=(const IntCell &rhs);
//Implementación
IntCell &IntCell::operator=(const IntCell &rhs) {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
    }
    return *this;
}
```
Si la dirección de memoria del valor rhs es diferente a la del lhs, el storedValue del lhs se iguala al storedValue del rhs.<br>
Si la dirección de memoria es la misma no se hace nada y se regresa.


## Operador = en caso de movimiento
```c++
//Interfaz
IntCell &operator=(IntCell &&rhs) noexcept;
//Implementación
IntCell &IntCell::operator=(IntCell &&rhs) noexcept {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0;
    }
    return *this;
}
```

Si la dirección de memoria del valor rhs es diferente a la del lhs, el storedValue del lhs se iguala al storedValue del rhs. Posterior mente se regresa el valor de de storedValue del rhs a defecto, en este caso 0. <br>
Si la dirección de memoria es la misma no se hace nada y se regresa.

## Operador = con una variable tipo *int*
```c++
//Interfaz
IntCell &operator=(int rhs);
//Implementación
IntCell &IntCell::operator=(int rhs) {
    storedValue = rhs;
    return *this;
}
```
El valor de la variable ths de tipo *int* se guarda en el storedValue de la clase y se retorna.<br>
