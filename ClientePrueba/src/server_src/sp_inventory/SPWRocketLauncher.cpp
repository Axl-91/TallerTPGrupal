#include "SPWRocketLauncher.h"


SPWRocketLauncher::SPWRocketLauncher(){
    type = ROCKET_LAUNCHER;
    before = std::chrono::high_resolution_clock::now();
    damage = ROCKET_LAUNCHER_DAMAGE;

}

SPWRocketLauncher::~SPWRocketLauncher(){}


float SPWRocketLauncher::shoot(float dist, shooting_state_t &shootingState){
    std::cout<<"disparo con el cañon"<<std::endl;   
    return damage;
}
