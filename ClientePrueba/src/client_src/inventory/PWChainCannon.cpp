#include "PWChainCannon.h"

std::vector<std::string> PWChainCannonSprites={
    "Media/WeaponSprites/PWChainCanon0.png",
    "Media/WeaponSprites/PWChainCanon1.png",
    "Media/WeaponSprites/PWChainCanon2.png",
    "Media/WeaponSprites/PWChainCanon3.png",
    "Media/WeaponSprites/PWChainCanon4.png"
};


PWChainCannon::PWChainCannon():
PlayerWeapon(PWChainCannonSprites){
    type=CHAIN_CANNON;
}

void PWChainCannon::render(int posX, int posY){
    std::cout<<"render CHAIN CANNON"<<std::endl;
}


PWChainCannon::~PWChainCannon(){}