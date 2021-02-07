#include "SPWKnife.h"



SPWKnife::SPWKnife(){
    type=KNIFE;
    damage=KNIFE_DAMAGE;
}
SPWKnife::~SPWKnife(){}

float SPWKnife::shoot(float dist, bool &isShooting){
    std::cout<<"disparo con cuchillo"<<std::endl;   
    if(shooting==false){
        isShooting=false;
        return 0;
    }
    if(dist>5){
        shooting = false;
        return 0;
    }

    shooting = false;
    return damage;
}
