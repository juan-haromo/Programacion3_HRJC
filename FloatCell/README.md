# FloatCell.h Documentation

La FloatCell intenta copiar la funcionalidad del primitivo float, copiando las funcionalidades de los 5 grandes, ademas de la posibilidad de dividir tanto entre FloatCell como con datos primitivos float.

## Constructor por defecto
```c++
//Interfaz
explicit FloatCell(float newValue = 0.0);
//Implementación
FloatCell::FloatCell(float newValue) : storedValue(newValue) {}
```
Puede aceptar un parámetro que sera guardado en la variable storedValue, de tipo float.<br>
Si no se proporcionan ningún parámetro, el valor por defecto es 0.0<br>

## Constructor por copia
```c++
//Interfaz
FloatCell(const FloatCell &rhs);
//Implementación
FloatCell::FloatCell(const FloatCell &rhs) : storedValue(rhs.storedValue) {}
```
En caso de crear una copia de esta clase, la variable storedValue del rhs, sera guardada en el storedValue del lhs.<br>

## Constructor de movimiento
```c++
//Interfaz
FloatCell(FloatCell &&rhs) noexcept;
//Implementación
FloatCell::FloatCell(FloatCell &&rhs) noexcept : storedValue(rhs.storedValue) {
    rhs.storedValue = 0.0;
}
```
Toma el storedValue del rhs, lo pasa al storedValue del lhs.<br>
Regresa el valor de de storedValue del rhs a defecto, en este caso 0.0<br>

## Operador = (Misma clase)
```c++
//Interfaz
FloatCell &operator=(const FloatCell &rhs);
//Implementación
FloatCell &FloatCell::operator=(const FloatCell &rhs) {
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
FloatCell &operator=(FloatCell &&rhs) noexcept;
//Implementación
FloatCell &FloatCell::operator=(FloatCell &&rhs) noexcept {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0.0;
    }
    return *this;
}
```

Si la dirección de memoria del valor rhs es diferente a la del lhs, el storedValue del lhs se iguala al storedValue del rhs. Posterior mente se regresa el valor de de storedValue del rhs a defecto, en este caso 0.0 <br>
Si la dirección de memoria es la misma no se hace nada y se regresa.

## Operador = con una variable tipo *float*
```c++
//Interfaz
FloatCell &operator=(float rhs);
//Implementación
FloatCell &FloatCell::operator=(float rhs) {
    storedValue = rhs;
    return *this;
}
```
El valor de la variable ths de tipo *float* se guarda en el storedValue de la clase y se retorna.<br>

## Operador / con una variable tipo *FloatCell*
```c++
//Interfaz
FloatCell operator/(FloatCell rhs);
//Implementación
FloatCell FloatCell::operator/(FloatCell rhs) {
    
    if(rhs.storedValue == 0){
        throw std::invalid_argument("Division by 0");
    }
    return FloatCell(storedValue/rhs.storedValue);
}
```
El operador / correspondiente a la division, si el divisor es igual a 0, se arroja un error, correspondiente al error matemático de dividir entre 0.<br>
Si el valor es diferente de 0, se genera una clase FloatCell con el parámetro del storedValue entre rhs.storedValue la cual se guardara en el lhs.<br>

## Operador / con una variable tipo *float*
```c++
//Interfaz
FloatCell operator/(float rhs);
//Implementación
FloatCell FloatCell::operator/(float rhs) {
    
    if(rhs == 0){
        throw std::invalid_argument("Division by 0");
    }
    return FloatCell(storedValue/rhs);
}
```

El operador / correspondiente a la division, si el divisor es igual a 0, se arroja un error, correspondiente al error matemático de dividir entre 0.<br>
Si el valor es diferente de 0, se genera una clase FloatCell con el parámetro del storedValue entre rhs de tipo float la cual se guardara en el lhs.