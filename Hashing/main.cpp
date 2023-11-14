#include<iostream>
#include <string>

std::string JcsHashing(std::string textToHash);

int main(){

    
    std::cout<<JcsHashing("P")<<std::endl;
    std::cout<<JcsHashing("Pa")<<std::endl;
    std::cout<<JcsHashing("Pab")<<std::endl;
    std::cout<<JcsHashing("Pabl")<<std::endl;
    std::cout<<JcsHashing("Pablo")<<std::endl;
    std::cout<<JcsHashing("Patlo")<<std::endl;
    std::cout<<JcsHashing("Pable")<<std::endl;

    return 0;
}

std::string JcsHashing(std::string textToHash){

    std::string hasedText{};

    int i = 0;
    int lastDigit = 1;

    while (i<textToHash.size()){
        int textToNumber = ((textToHash[i] * 19) * textToHash.size())  + lastDigit;
        lastDigit = textToNumber % 10;
        hasedText += std::to_string(textToNumber);
        i++;
    }
    return hasedText; 
}

std::string JcsUnHashing(std::string textToUnHash){

    std::string unHasedText;

    return unHasedText;
}