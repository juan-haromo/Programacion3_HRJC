#ifndef FLOATCELL_H
#define FLOATCELL_H

#pragma once

class FloatCell
{
public:
    
    //Constructor
    explicit FloatCell(float newValue = 0.0);
    FloatCell(const FloatCell &rhs);
    FloatCell(FloatCell &&rhs) noexcept;
    //Operators
    FloatCell &operator=(const FloatCell &rhs);
    FloatCell &operator=(FloatCell &&rhs) noexcept;
    FloatCell &operator=(float rhs);
    FloatCell operator/(FloatCell rhs);
    FloatCell operator/(float rhs);
    //Methods
    float GetStoredValue();
    void SetStoredValue(float newValue);

private:
    float storedValue;
};

#endif