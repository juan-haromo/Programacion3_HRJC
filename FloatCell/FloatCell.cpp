#include "FloatCell.h"
#include <stdexcept>

//Constructors
FloatCell::FloatCell(float newValue) : storedValue(newValue) {}

FloatCell::FloatCell(const FloatCell &rhs) : storedValue(rhs.storedValue) {}

FloatCell::FloatCell(FloatCell &&rhs) noexcept : storedValue(rhs.storedValue) {}

//Operators
FloatCell &FloatCell::operator=(const FloatCell &rhs) {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
    }
    return *this;
}

FloatCell &FloatCell::operator=(FloatCell &&rhs) noexcept {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0.0;
    }
    return *this;
}

FloatCell &FloatCell::operator=(float rhs) {
    storedValue = rhs;
    return *this;
}

FloatCell FloatCell::operator/(FloatCell rhs) {
    
    if(rhs.storedValue == 0){
        throw std::invalid_argument("Division by 0");
    }
    return FloatCell(storedValue/rhs.storedValue);
}

FloatCell FloatCell::operator/(float rhs) {
    
    if(rhs == 0){
        throw std::invalid_argument("Division by 0");
    }
    return FloatCell(storedValue/rhs);
}

//Methods
float FloatCell::GetStoredValue(){
    return storedValue;
}

void FloatCell::SetStoredValue(float newValue){
    storedValue = newValue;
}
