#include "PWChainCannon.h"

std::vector<std::string> PWChainCannonSprites={
    "Media/WeaponSprites/PWChainCanon0.png",
    "Media/WeaponSprites/PWChainCanon1.png",
    "Media/WeaponSprites/PWChainCanon2.png",
    "Media/WeaponSprites/PWChainCanon3.png",
    "Media/WeaponSprites/PWChainCanon4.png"
};


PWChainCannon::PWChainCannon(shooting_state_t &sS):
PlayerWeapon(sS, PWChainCannonSprites){
    type=CHAIN_CANNON;
    frameTime = CHAIN_CANNON_FRAME_TIME;
}

void PWChainCannon::render(int posX, int posY){
    // int delay = 2;

    int frame = 0;
    //    std::cout<<"render shoot chain connon";
    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);

    std::cout<<"frame: "<<frame<<std::endl;

    if (shootingState != SHOOTING_STATE_QUIET){
        if(waited.count()>=frameTime){
            numAuxiliar++;
            before=now;
        }
        frame = numAuxiliar;

        if (shootingState == SHOOTING_STATE_SHOOTING){
            if (frame > 3){
                numAuxiliar = 1;
                frame = numAuxiliar;
               // shootingState=SHOOTING_STATE_QUIET;
            }
        }else
         if (frame > 4){
             numAuxiliar = 0;
             frame = 0;
             shootingState=SHOOTING_STATE_QUIET;
        }
    }
    std::cout<<"frame: "<<frame<<std::endl;

    textureHandler.render(96, 72, GUNL, GUNA, frame);

    // std::cout<<"render CHAIN CANNON"<<std::endl;
}


PWChainCannon::~PWChainCannon(){}