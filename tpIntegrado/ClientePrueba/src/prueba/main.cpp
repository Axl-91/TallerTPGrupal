#include <iostream>
#include <map>
#include "Vector.h"

int main(void){
    std::map <std::pair<int,int>,int>m;
    std::pair<int,int> a(0, 1);
    std::pair<int,int> a1(1, 2);
    std::pair<int,int> a2(2, 3);
    std::pair<int,int> a3(57, 4);
    std::pair<int,int> a4(109, 5);
    std::pair<int,int> b=a;

    m[a]=10;
    m[a1]=11;
    m[a2]=12;
    m[a3]=13;
    m[a4]=14;

    std::cout<<"hola"<<std::endl;
    std::cout<<m[b]<<std::endl;
    b={1,2};
    std::cout<<m[b]<<std::endl;
    m.erase(a1);

    std::cout<<m[b]<<std::endl;

    std::cout<<"hola"<<std::endl;
}