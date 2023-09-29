#include "DoubleCell.h"
#include <stdexcept>

// Default constructor
//If no value given initializes stored value as 0.0
DoubleCell::DoubleCell()
        :storedValue(0.0){}

// Constructor with value
//If a creation value given it will be stored in storedValue
DoubleCell::DoubleCell(double value)
        : storedValue(value){}

// Copy constructor
//Copies all values stored into the new Double cell
DoubleCell::DoubleCell(const DoubleCell &other)
        : storedValue(other.storedValue){}

//Reference  constructor
//Copies all values stored into the new Double cell
//And then makes the value of the rhs cell default (0.0)
DoubleCell::DoubleCell(DoubleCell &&other) : storedValue(other.storedValue) {
    other.storedValue = 0.0;
}


// Destructor
//Uses default destructor as it works for this class
DoubleCell::~DoubleCell() = default;

// Assignment operator by copy
//Copies al data members of the rhs into the lhs
DoubleCell &DoubleCell::operator=(const DoubleCell &other){
    if (this != &other){
        storedValue = other.storedValue;
    }
    return *this;
}

// Assignment operator by reference
DoubleCell &DoubleCell::operator=(DoubleCell &&other){
if(this != &other){
storedValue = other.storedValue;
other.storedValue = 0.0;
}
return *this;
}

// Assignment operator for double
//If a double is assigned
DoubleCell &DoubleCell::operator=(double value){

    storedValue = value;

    return *this;
}

// Arithmetic operators


//DoubleCell adding
DoubleCell DoubleCell::operator +(const DoubleCell& other) const{
    return DoubleCell(storedValue + other.storedValue);
}
//primitive double adding
DoubleCell DoubleCell::operator +(const double other) const{
    return  DoubleCell(storedValue + other);
}
//DoubleCell substracting
DoubleCell DoubleCell::operator-(const DoubleCell &other) const {
    return  DoubleCell(storedValue - other.storedValue);
}

//primitive double substracting
DoubleCell DoubleCell::operator -(double value) const{
    return DoubleCell(storedValue - value);
}

//DoubleCell multiplication
DoubleCell DoubleCell::operator *(const DoubleCell& other) const{
    return DoubleCell(storedValue * other.storedValue);
}
//primitive double multiplication
DoubleCell DoubleCell::operator*(const double other) const {
    return  DoubleCell(storedValue + other);
}
//DoubleCell division
DoubleCell DoubleCell::operator /(const DoubleCell& other) const{
    if(other.storedValue == 0){
        throw std::invalid_argument("Division by zero");
    }
    return DoubleCell(storedValue / other.storedValue);
}

//Primitive double division
DoubleCell DoubleCell::operator /(double value) const{
    if(value == 0){
        throw std::invalid_argument("Division by zero");
    }
    return DoubleCell(storedValue / value);
}

// Setters
void DoubleCell::SetValue(double value){
    storedValue = value;
}

// Getters
double DoubleCell::GetValue() const {
    return  storedValue;
}
