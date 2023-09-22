# Resumen capitulo 1 "Data Structures and Algorith Analysis in C++"

El capitulo, y el libro comienza planteándonos su propósito, existen infinitos problemas de programación, cada una con multiples resultados, pero no todos son igual de eficientes, por lo que se debe analizar la forma en que estos mismos están estructurados. 

Después de procede a una revision de conceptos matemáticos, como los exponentes y sus comportamientos en operaciones matemáticas.

Posteriormente se hable de los *logaritmos*, los cuales personalmente me son desconocidos en el que y como, por lo que procedo a expandir un poco: 

> "Los logaritmos se pueden considerar como otra forma de ver los exponentes ..."<br> 
>
>"Mientras que los exponentes de la forma<br>
>
>$$ x^n = *y *$$  
>corresponden a elevar un valor *x* a la potencia *n*, obteniendo *y*"<br>
>
>"Mientras que los logaritmos responden a la pregunta: A que potencia *n* se debe elevar *x* para obtener *y*?..."<br>
>
>"Por lo cual los logaritmos son otra forma de expresar la relación entre una base, su exponente y su valor..." <br>
>
>"Siendo que los logaritmos cuentan con la forma: <br>
>$$log~x(y) = n$$
>De esta manera ambas muestran la relación de *x*, *n*,*y*.<br>
>Donde:
>- *x* es la base<br>
>- *n* el exponente 
>- *y* el argumento
>
>Fuente: [1]	“Intro to logarithms”, Khan Academy. [En línea]. Disponible en: https://www.khanacademy.org/math/algebra2/x2ec2f6f830c9fb89:logs/x2ec2f6f830c9fb89:log-intro/a/intro-to-logarithms. [Consultado: 18-sep-2023].<br>

Prosigue el capitulo abarcando el tema de series, asi como algunas de sus propiedades y formulas. <br>
Siendo las series el sumar de manera repetitiva un numero desde una base hasta *N* donde se sabe en que paso de la seria se va gracias a *i* que inicia en el valor inicial y termina en *N*.<br>

Continua con la aritmética modular, la cual consta de de que el modulo *N* es el mismo para un numero *A*, *B*, etc... asi como las propiedades que estas tienen. <br>

El siguiente punto nos habla de la *P Word* o comprobación (*proof* en ingles)<br>
La cual en este caso se usa para comprobar afirmaciones en estructuras de datos. Existiendo 2 formas principales 
1. Inducción <br>
 La cual consta de los siguientes pasos: <br>
    1. Comprobar un caso base
    2. Estableces un teorema para un grupo reducido de casos
    3. Asumir una hipótesis
    4. Comprobar para un limite máximo k
    5. Demostrar para el caso k+1
    6. Demostrar o negar el teorema
2. Contradicción <br>
    - Esta forma de prueba parte del asumir que el teorema es falso
    - Después se intenta demostrar, con el objetivo de llegar a una contradicción
    - Implicando asi que el teorema es verdadero

Después de esto, se llega a la recursion, la según el propio libro se define como:<br>

>"Una función que esta definida en términos de si misma"<br>
>
> [2]	M. A. Weiss, Data Structures and Algorithm Analysis in C++, 4a ed. Upper Saddle River, NJ, Estados Unidos de América: Pearson, 2013. <br>

Este tipo de funciones se contienen asi mismas, y cada vez que se llaman asi mismo lo hacen acercándose mas a un caso base, el cual no contiene recursividad y puede regresar a un valor mismo. <br>
En toda función recursiva debe existir un caso base alcanzable y al cual se pretenda acercarse mas con cada llamada recursiva, ya que de otra forma la función se considera como indefinida.  <br>
Enseguida se pasa a hacer una comprobaciones usando recursion y dando un ejemplo de recursion.<br>
Mientras que mas adelante encontramos 4 reglas básicas para poder diseñar un algoritmo recursivo:
1. Tener casos base que no requieran de recursion
2. Cada vez que se realiza una llamada recursiva esta debe acercarse al caso base
3. Asumir que todos los casos recursivos deben funcionar
4. Nunca resolver el mismo caso en dos llamadas recursivas distintas

Ejemplo de función recursiva en C++
```c++
  int factorial(int x){
    if(x>=0){
        return 1;
    }
    else{
        return x * factorial(x - 1);
    }
  }
```

El siguiente sub-tema del capitulo son las clases en C++<br>

Estas son estructuras de datos las cuales consisten de miembros, que pueden ser datos o funciones/métodos.

En el siguiente bloque se puede observar una clase y sus elementos 

```c++
//Revisa si la clase ya fue definida
#ifndef Car.h
//Si no lo ah sido la define, si ya fue definida no la redefine para evitar problemas
#define Car.h

class Car(){

  //Encapsulamiento: Define el nivel de acceso de los miembros

  public: // Cualquiera puede acceder 
  //Datos
  std::string color; 
  float actualSpeed;
  //Métodos
  void StartEngine(); 
  void Accelerate();
  void ShowActualSpeed();
  private: //Solo se puede acceder dentro de la propia clase
  float maxSpeed;
  void SetMaxSpeed();
}


Car::Car(){ // Constructor por defecto generado automáticamente  implícito
}

Car::Car(std::string chosenColor){
  //Constructor con parámetros, que inicializa valores según los parámetros explicito
  color = chosenColor;
}

Car::~Car(){ // Destructor sirve para eliminar y liberar la memoria tomada por la clase 
}

//solo se pueden crear clases mediante constructores

/*No se pueden igualar dos clases distintas
Human human1;
Car car1 = human1 **Error**
*/


#endif
```
El código anterior corresponde a la interfaz, en la cual se pueden ver los elementos de la clase. Se encuentran en un archivo de tipo .h <br>
La interfaz, por otra parte se suele implementar en otro archivo con terminación .cpp\

```c++
#include "Car.h"

//Un acceso lee los datos de la funcion pero no cambia sus estado
Car::void ShowActualSpeed(){
  std::cout<<actualSpeed<<" km/h"<<std:endl;
}

//Un mutador cambia el estado del objeto
 Car::void Accelerate(){
  if(actualSpeed<maxSpeed){
    actualSpeed++;
  }
 }

 // Los :: en medio de la clase y el tipo son el Scope resolution operator y se usa para identificar el método en la clase y no globalmente
```

Las clases se implementan como las clases primarias 
```c++
#include<iostream>
#include"Car.h"

int main(){

  int n;
  Car car1("red");

  return 0;
}
```

Se continua con 2 clases estándar de C++, el vector y el string.
Un string es un arreglo de caracteres.
Un vector es una clase mas avanzada que un arreglo, cuenta con la misma funcionalidad base mas otras como el poder ser comparados y contener su propio tamaño.<br>
Mientras que los vectores  son objetos capaces de contener con tantos elementos como se necesiten.

La sintaxis es la siguiente
```c++
std::vector<type> vector1;
```
cuenta con sus propios métodos como size y capacity.

Se sigue con las particulares del C++, entre las que encontramos. <br>

Los punteros, los cuales son variables que guardan direcciones de memoria de otras variables y pueden acceder a su contenido. Su sintaxis es
```
c++
int *var1 = &var2;
```
<br>
En el nombre de la variable se debe poner un * mientas que para el valor igualado se debe poner un & para indicar que debe apuntar a la dirección de memoria y no al contenido. Siendo importante que los punteros pueden redireccionarse a otra dirección de memoria y pueden ser eliminados mediante la palabra reservada *delete*<br>
o
De igual manera se pueden crear objetos dinámicos mediante punteros usando la siguiente sintaxis 
```c++
MyObject *myPointer = new MyObject;
```
De esta manera se creara un objeto que sera redirigido al puntero<br>
Otras de las características mencionadas es el colector de basura, el cual a diferencia de otros lenguajes ***No*** es automático, por lo cual se debe usar el operador *delete* mediante un puntero, de otra manera la memoria usada por dicho objeto no sera liberada hasta el fin del programa o que la función en la que se encuentra haga un *return*.<br>
Otra de las funciones de este lenguaje es la comparación de punteros, la cual sera verdad, si y solo si apuntan a la misma dirección de memoria. En caso de asignar un puntero lhs a un puntero rhs, hace que el lhs apunte a la misma dirección que el rhs.<br>
Para acceder a un miembro de una clase se puede hacer de las siguientes formas 
```c++
//Si es una variable de la clase del objeto
myObj.helloWorld();
//Si es un puntero al un objeto
myObj2->helloWorld();
```

Entre los detalles de C++ también encontramos lo Lvalores y los Rvalores. Los LValores (llamados asi porque se encuentras a la izquierda de una asignación *left values*) son objetos no temporales en donde se guarda información. Mientras que los Rvalores (*right values* debido a que se encuentran a la derecha de una asignación) son expresiones que identifican un valor, el cual sera almacenado en un Lvalor
```c++
//Lvalor = Rvalor;
int var = 5;
``` 
Una referencia permite definir un nuevo nombre para un valor existente, desde C++11 se pueden tener 2 tipos de referencias, las referencias Lvalor y las referencias Rvalor.<br>

Una referencia Lvalor se declara de la siguiente forma:
```c++
int val1 = 5;
int & val2 = val1;
```
Siendo que de esta manera se convierte en un sinónimo de la otra variable. Esto ofrece varias funciones como
1. Simplificar expresiones complicadas.
2. Como rango en un ciclo for each modificable.
3. Evitar crear copias de variables.

Mientras que las referencias Rvalor se declaran: 
```c++
std::string && mystr = "hello"
```
Pero su función es descrita mas adelante y requiere de contexto, por lo cual eso bastara por ahora.<br>

Otra de las funciones de c++ es el paso de parámetros, los cuales, desde C++11 son 4:
1. Llamada por valor (***call by value***)<br>
  ```c++
  double add(double a, double b);
  ```
  En este tipo los valores son copiados dentro de la función, el código ejecutado y el resultado regresado.<br>

2. Llamada por referencia (***call by reference***) 
```c++
void swap(double & a, double & b);
```
En este tipo de valores se pasa por referencia, por lo que se modificado en *a* o *b* serán también modificados en los valores originales.<br>

3. Llamada por referencia constante ***call by constant reference.***
```c++
std::string longestWord(const vector<std::string> & randomWords);
```
En este tipo de referencias se pasa una  referencia la cual no puede ser modificada, permitiendo analizar objetos de mayor peso sin la necesidad de hacer una copia y sin el riesgo de modificar los valores llamados.

4. Llamada por referencia de Rvalor ***call by rvalue reference***
```c++
std::string randomItem( vector<std::string> && arr );
```

Este tipo de llamada se usa para mover un objeto en lugar de copiarlo (lo cual mas eficiente), este método es comúnmente usado para definir el comportamiento de *=* y al elaborar constructores.<br>


Mientras que en contraparte a esto encontramos los retornos, que es la forma de sacar un valor fuera de una función. Existen numerosos métodos entre ellos encontramos 
* Regreso por valor (*return by value*). En este mecanismo se regresa un valor u objeto del tipo de la fusion que sera almacenado en un Lvalor
```c++
double addition(double a, double b){
  //Regresa un Rvalor, en este caso de tipo double
  return a + b;
}

//El regreso se guarde en un Lvalor, generando una copia
double lval = addition (5,3);
```

* Regreso por referencia constante (*return by constant reference*). Este método toma ventaja de que los parámetros que son Lvalues y existirán después de la función, creando asi una copia. Para usar este método se necesita que los parámetros sean referencias constantes, asi como que el Lvalor donde ser guardara la referencia también sea una.
```c++
const LargeType & randomItem2( const vector<LargeType> & arr ){
return arr[ randomInt( 0, arr.size( ) - 1 ) ];
}
```

* Regreso por referencia (*return by reference*). Esta forma permite que el llamado de una función pueda modificar su acceso a los datos internos.

Otras de las funciones que encontramos en c++  son std::swap y std::move.<br>
std::move permite hacer que un Lvalor (o rValor) se convierta en un r valor y pueda ser movido, evitando asi el costo de crear copias a la hora de igualar un valor a otro.
std::swap cambia los valores de los dos parámetros pasados a y b
```c++
template< class T >
void swap( T& a, T& b );
```
>Definición de std::swap de C++ 11 a C++ 20, encontrada en el header \<utility>
>[2]	“Std::Swap”, Cppreference.com. [En línea]. Disponible en: https://en.cppreference.com/w/cpp/algorithm/swap. [Consultado: 20-sep-2023].

Otras de las funciones con las que cuenta C++ son conocidas como los 5 grande.<br>
Estas son funciones prescritas de las clases, las cuales son:<br>
* ***Destructor*** <br>
  Es el encargado de liberar la memoria ocupada por un objeto, se activa cuando este sale del *scope* o es destruido mediante *delete*. Por defecto los destructores se aplican a cada miembro de la función<br>
* ***Move & copy constructor***
  Son constructores usados para construir un objeto inicializando con otro. Si el objeto es un Lvalor se genera una copia, mientras que si es un Rvalor se generara un movimiento.<br>

  ```c++
  MyObj obj1 = lValObj; // Copy constructor
  MyObj obj2 = rValObj //Move constructor 
  ```
  Por defecto la copia del constructor asignara los mismos valores primitivos a la nueva clase (int, float, char...), mientras que para los miembros que sean clases se aplicara el proceso de la propia clase.<br>

***Copy assignment an move assignment (operador =)***
  Se emplean cuando se usa el operador = a dos objetos previamente creado. Si el rhs es un Lvalor se usara el asignado de copia (*copy assignment*) mientras que si es un Rvalor se empleara la asignación de movimiento (*move assignment*). Por defecto estos copean el valor de cada miembro.
  
  
Las funciones por defecto de los 5 grandes funcionan normalmente, a menos que se usen miembros que sea punteros. En cuyo caso el puntero sera copeado y apuntado al mismo objeto, esto es conocido como  *copia superficial* (*"Shallow copy"*  en ingles), si se desea hacer una copia del objeto al cual se esta apuntando, se debe realizar una *copia profunda* (*deep copy* en ingles).<br>

Por lo cual cuando se emplean punteros o semánticas complicadas estos deben ser declarados explícitamente, si se requiere declarar 1 de los 5, por buena practica los 5 deben se explícitos. De lo contrario uno de estos se puede volver invalido o inapropiado y llevar a problemas como *memory leaks* (perdidas de memoria).<br>

La ultima característica contenida en el capitulo son los arreglos tipo-C, los cuales se declaran de la siguiente forma 
```c++
int arr[10];
```
Los cuales, son punteros y no clases, los cuales no se les puede aplicar el operador =, son punteros constantes, no pueden saber el tamaño, ni usar indices, debido al uso del carácter \0 para indicar el final del mismo.<br>
Ademas de esto cuentan con todos los problemas asociados a los arreglos. Por lo cual generalmente es mejor usar los objetos \<vector> y \<string>, excepto que se necesite optimizar el código en una determinada sección.

Luego, nos encontramos con el topico de las *plantillas* o *templates* las cuales son usadas para crear algoritmos o estructuras de datos cuyo tipo (int, float, string...) es indiferente.<br>
**Plantillas de funciones**: No son funciones sino un un patron que segun el tipo de datos se convierte en una funcion.  Debido a que estas plantillas pueden tomas cualquier tipo, su paso-retorno de parametros se realiza mediante referencias constantes. Una plantilla de funcion se ve de la siguiente manera: 
```c++
//Este codigo solo aceptaria parametros de clases que cuenten con el comparado < declarado
template <type ComparableType>
void  BubbleSort (vector<ComparableType> & vec){
    for(int i = 0, i<vec.size(), i++){
      for(int j = 1, j<vec.size()-i,j++){
        if(vec[j - 1]>vec[j]){
          std::swap(vec[j -q],vec[j]);
        }
      }
    }
}
```
**Plantillas de clases**: Son clses que puede recibir cualquier tipo de dato. Un ejempo de esto es la clase vector, la cual puede recibir cualquier tipo de clase para su creación.
```c++
template <type T>
vector<T>
```

Otra de las características de las clases de C++, es que estas pueden ser *Objetos* y *Comparables*.<br>
*Los objetos* tiene un constructor sin parámetros, un *operador=* y un constructor por copia.
*Los comparables* estos ademas de cuentan con el *operador<*, los cual permite darles orden.<br>
Asi mismo se puede configurar el *operador<<* para una clase, ejemplo:
```c++
class car{
  private: 
  std::string name;
  float maxSpeed;

  //Configuración del operador<
  bool operator<(const Car & rhs) const{
    return maxSpeed < rhs.maxSpeed;
    //En este ejemplo se compara el miembro maxSpeed, pero se podría comparar otro miembro o una función return
  }

  //Función para imprimir
  void print(ostream & out = cout) const{
    out <<"car name"<<car.name<<std::endl;
  }

  //Configuración del operador <<
  ostream & operator<< (ostream & out, const Car & rhs){
    rhs.print(out);
    return out;
  }

}
```

Otra de las características las características que no encontramos son las *funciones objeto*, las cuales son clases que no contienen ningún miembro dato, pero si miembros funciones, por lo cual pueden ser  usados como parámetros en otra función para asi cambiar los métodos utilizados en esta<br>

Por otra parte tenemos que las clases plantilla al igual que las clases normales se pueden separar en interfaz e implementación, pero esto puede dar problemas entre plataformas, por lo que se suelen mantener ambas en un único archivo .h. <br>
Por último en el capítulo, C++ no ofrece una clase matriz para usar arreglos bidimensionales, sin embargo pueden ser implementadas mediante un vector de vectores, creándolas y accediendo las mediante el operador [] en dónde m[x] regresará un vector, mientras que m[x][y] devolverá el objeto contenido. Debido a la naturaleza propia de los vectores, las matrices pueden guardar cualquier tipo de dato o clase.<br>

***Opinion critica***<br>
EL capitulo uno del libro es uno bastante condesado, parte del hecho que sabes que es de lo que están hablando, por lo cual esta comprimidos. Sin embargo los temas son importantes. <br>
Primero los conceptos matemáticos (excepto los logaritmos), son temas básicos y que ya habíamos visto en algún punto de nuestro estudio. Aun asi el resumen rápido para un repaso es siempre util.
Las clases fue un tema básico, muy básico y que posteriormente en los detalles salta el nivel de complejidad, por lo que es un temas un poco mal planteado, ya que se salta muchos paso y hace que el propio libro tenga agujeros de conocimiento.<br>
Las características de c++ es un tema bastante básico, pero aun asi interesante ya que muchas cosas se sabían hacer pero no el que son y porque son, por lo que esta bien planteado, entrando desde un punto muy básico y util. Mientras que la inclusion explicita de los 5 grandes y como afectan es un punto muy a favor y util de esta lectura.<br>
Las plantillas son algo simple, pero aun asi util por lo que este capitulo fue muy util ya que facilitan la refactorizacion de código al no necesitar hacerlo para cada tipo de variable, pero aun asi dando la oportunidad de cambiar si fuera necesario.<br>
Y las matrices siendo el tema mas simple, corto pero util ya que permite tener una mayor estructura de datos organizadas. Corto pero conciso, buen tema<br>


***Opinion personal***<br>
Los temas del son algo densos, sin embargo son buenos ya que sirvieron para ver huecos en el conocimiento, por lo que fueron buenos para dar un repaso y un *speedrun* de los temas faltantes de otros semestres, en especial los 5 grandes y otras particularidades de las clases ya que no había visto nada del tema, el cual es muy importante ya que los objetos son la parte fundamental de C++ y por lo tanto necesario para poder trabajar de manera correcta el lenguaje. También fue bueno para sentar unas buenas bases de programación semántica y lógica para escribir código de calidad. Ademas en este temas creo que se debería repasar algunos temas, no completamente incluidos en el libro, pero algunas sintaxis utilizadas, en especial durante la sección de los 5 grandes.  <br>

**Referencias**

[1]	“Intro to logarithms”, Khan Academy. [En línea]. Disponible en: https://www.khanacademy.org/math/algebra2/x2ec2f6f830c9fb89:logs/x2ec2f6f830c9fb89:log-intro/a/intro-to-logarithms. [Consultado: 18-sep-2023].

[2]	M. A. Weiss, Data Structures and Algorithm Analysis in C++, 4a ed. Upper Saddle River, NJ, Estados Unidos de América: Pearson, 2013.