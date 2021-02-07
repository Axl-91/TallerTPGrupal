#include "PWGun.h"

std::vector<std::string> PWGunSprites={
    "Media/WeaponSprites/PWGun0.png",
    "Media/WeaponSprites/PWGun1.png",
    "Media/WeaponSprites/PWGun2.png",
    "Media/WeaponSprites/PWGun3.png",
    "Media/WeaponSprites/PWGun4.png"
};

PWGun::PWGun():
PlayerWeapon(PWGunSprites){
    type=GUN;
}


void PWGun::render(int largoWin, int altoWin){
    int delay = 10;
    int frame = 0;

    if (shootingState!=SHOOTING_STATE_QUIET){
        numAuxiliar++;
        frame = numAuxiliar/ delay;

         if (frame > 4){
             numAuxiliar = 0;
             frame = 0;
             shootingState=SHOOTING_STATE_QUIET;
        }
    }
    textureHandler.render(96, 72, GUNL, GUNA, frame);
}


PWGun::~PWGun(){}
