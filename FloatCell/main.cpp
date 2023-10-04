#include <iostream>
#include "FloatCell.h"


int main(){

    FloatCell floatCell1(5.12);
    FloatCell floatCell2;

    std::cout<<"The value of cell 1 is: " << floatCell1.GetStoredValue()<<std::endl;
    std::cout<<"The value of cell 2 is: " << floatCell2.GetStoredValue()<<std::endl;
    floatCell2 = floatCell1;
    floatCell2 = floatCell2/2.0;
    std::cout<<"The new value of cell 2 is: "<< floatCell2.GetStoredValue()<<std::endl;
    
    return 0;
}