#include "SPWChainCannon.h"

SPWChainCannon::SPWChainCannon(){
    type=CHAIN_CANNON;
    before = std::chrono::high_resolution_clock::now();
    damage = CHAIN_CANNON_DAMAGE;

}

SPWChainCannon::~SPWChainCannon(){}

float SPWChainCannon::shoot(float dist, bool &isShooting){
    std::cout<<"diasparo con el chain Canon"<<std::endl;
    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);

    if(waited.count()<CHAIN_CANNON_WAIT_TIME)
        return 0;

    return damage;

}
