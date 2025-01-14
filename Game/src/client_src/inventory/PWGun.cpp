#include "PWGun.h"

std::vector<std::string> PWGunSprites={
    "Media/WeaponSprites/PWGun0.png",
    "Media/WeaponSprites/PWGun1.png",
    "Media/WeaponSprites/PWGun2.png",
    "Media/WeaponSprites/PWGun3.png",
    "Media/WeaponSprites/PWGun4.png"
};

PWGun::PWGun(shooting_state_t &sS):
PlayerWeapon(sS, PWGunSprites){
    type=GUN;
    frameTime = GUN_FRAME_TIME;
}


void PWGun::render(int largoWin, int altoWin){
    int frame = 0;
    
    now = std::chrono::high_resolution_clock::now();
    auto waited = std::chrono::duration_cast<std::chrono::milliseconds>(now - before);

    if (shootingState!=SHOOTING_STATE_QUIET || frameAuxiliar!=0){
        if(waited.count()>=frameTime){
            frameAuxiliar++;
            before=now;
        }
        frame = frameAuxiliar;

        if (!soundOn){
            gunSounds->playEffect(GUN_SHOT, 20);
            soundOn = true;
        }

        if (frame > 4){
             frameAuxiliar = 0;
             frame = 0;
             soundOn = false;
             shootingState=SHOOTING_STATE_QUIET;
        }
    }
    textureHandler.render(posXWeapon, posYWeapon, GUNL, GUNA, frame);
}


PWGun::~PWGun(){}
