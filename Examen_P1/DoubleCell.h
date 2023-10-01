#ifndef DOUBLE_CELL_H
#define DOUBLE_CELL_H

class DoubleCell {
public:
    // Default constructor
    DoubleCell();

    // Constructor with value
    explicit DoubleCell(double value);

    // Copy constructor
    DoubleCell(const DoubleCell &other);

    //Reference constructor
    DoubleCell(DoubleCell &&other);

    // Destructor
    ~DoubleCell();

    // Assignment operator by copy
    DoubleCell &operator=(const DoubleCell& other);

    // Assignment operator by reference
    DoubleCell &operator=(DoubleCell &&other);

    // Assignment operator for double
    DoubleCell& operator=(double value);

    // Arithmetic operators

    //DoubleCell adding
    DoubleCell operator +(const DoubleCell& other) const;
    //primitive double adding
    DoubleCell operator +(const double other) const;
    //DoubleCell substracting
    DoubleCell operator -(const DoubleCell& other) const;
    //primitive double substracting
    DoubleCell operator -(const double other) const;
    //DoubleCell multiplication
    DoubleCell operator *(const DoubleCell& other) const;
    //primitive double multiplication
    DoubleCell operator *(const double other) const;
    //DoubleCell division
    DoubleCell operator /(const DoubleCell& other) const;
    //Primitive double division
    DoubleCell operator /(const double other) const;

    // Setters
    void SetValue(double value);
    // Getters
    [[nodiscard]]double GetValue() const;


protected:
    double storedValue;
};

#endif  // DOUBLE_CELL_H
