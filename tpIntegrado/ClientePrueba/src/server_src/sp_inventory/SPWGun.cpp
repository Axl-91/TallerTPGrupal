#include "SPWGun.h"

SPWGun::SPWGun(){
    type=GUN;
}
SPWGun::~SPWGun(){}

void SPWGun::shoot(){
    std::cout<<"disparo con pistola"<<std::endl;   
}
