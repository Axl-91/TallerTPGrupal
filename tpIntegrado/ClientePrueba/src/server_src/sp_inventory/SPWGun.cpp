#include "SPWGun.h"

SPWGun::SPWGun(){
    type=GUN;
}
SPWGun::~SPWGun(){}

float SPWGun::shoot(float dist, bool &isShooting){
    if(shooting==false){
        isShooting=false;
        return 0;
    }
    std::cout<<"disparo con pistola"<<std::endl;   
    shooting=false;
    return 10;
}
