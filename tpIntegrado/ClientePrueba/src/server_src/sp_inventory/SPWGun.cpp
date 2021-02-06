#include "SPWGun.h"

SPWGun::SPWGun(){
    type=GUN;
}
SPWGun::~SPWGun(){}

float SPWGun::shoot(float dist, bool &isShooting){
    isShooting=false;
    std::cout<<"disparo con pistola"<<std::endl;   
    return 10;
}
