#include <iostream>
#include<bitset>

int main(){
    std::string a = "1101";       // a = 101
    std::string b = "0011"; 
    //int b = a<<3;    // b = 101000 shift to right by 3
    //std::cout<<b;    // prints 40

    
    std::bitset<8> a1{a};
    std::bitset<8> b1{b};

    int size=8;
    std::cout << a1<<std::endl ;

    a1 = b1;
    std::cout << a1<<std::endl ;
    std::cout << a1[3]<<std::endl ;
}