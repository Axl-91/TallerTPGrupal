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
    int frame = 0;
    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);

    if (shootingState != SHOOTING_STATE_QUIET){
        if(waited.count()>=frameTime){
            frameAuxiliar++;
            before=now;
        }
        frame = frameAuxiliar;

        if (shootingState == SHOOTING_STATE_SHOOTING){
            if (!soundOn){
                gunSounds.playEffect(MINIGUN_SHOT, 20);
                soundOn = true;
            }
            if (frame > 3){
                frameAuxiliar = 1;
                soundOn = false;
                frame = frameAuxiliar;
            }
        }else if (frame > 4){
             frameAuxiliar = 0;
             frame = 0;
             soundOn = false;
             shootingState=SHOOTING_STATE_QUIET;
            }
        }
    textureHandler.render(posXWeapon, posYWeapon, GUNL, GUNA, frame);

}

PWChainCannon::~PWChainCannon(){}
