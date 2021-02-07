#include "SPWMachineGun.h"

SPWMachineGun::SPWMachineGun(){
    type=MACHINE_GUN;
    before = std::chrono::high_resolution_clock::now();
    damage = MACHINE_GUN_DAMAGE;
    bulletsCounter=1;
}

SPWMachineGun::~SPWMachineGun(){}


float SPWMachineGun::shoot(float dist, bool &isShooting){
    std::cout<<"disparo con LA MACHINE GAN"<<std::endl;   
    std::cout<<"bullet: "<<bulletsCounter<<std::endl;   

    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);
 
    if(bulletsCounter=MACHINE_GUN_BULLET_COUNTER){
        if(waited.count()<MACHINE_GUN_WAIT_TIME)
            return 0;
        bulletsCounter=1;
        return damage;
    }

    if(waited.count()<MACHINE_GUN_BULLET_WAIT_TIME)
        return 0;

    bulletsCounter++;
    return damage;
}
