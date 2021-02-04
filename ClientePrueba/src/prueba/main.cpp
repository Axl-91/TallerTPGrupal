#include <iostream>
#include <map>
#include "Vector.h"

int main(void){
    Vector a(4,6);
    Vector b(7,7);
    Vector c(0,2);
    std::cout<<c.getAngle(b-a)<<std::endl;
}