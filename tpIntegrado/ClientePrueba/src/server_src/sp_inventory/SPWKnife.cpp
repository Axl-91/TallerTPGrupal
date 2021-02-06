#include "SPWKnife.h"



SPWKnife::SPWKnife(){
    type=KNIFE;
}
SPWKnife::~SPWKnife(){}

float SPWKnife::shoot(float dist, bool &isShooting){
    if(dist>5)
        return 0;
    return 10;
    std::cout<<"disparo con cuchillo"<<std::endl;   
}
