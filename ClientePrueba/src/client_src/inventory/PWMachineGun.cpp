#include "PWMachineGun.h"

std::vector<std::string> PWMachineGunSprites={
    "Media/WeaponSprites/PWMachineGun0.png",
    "Media/WeaponSprites/PWMachineGun1.png",
    "Media/WeaponSprites/PWMachineGun2.png",
    "Media/WeaponSprites/PWMachineGun3.png",
    "Media/WeaponSprites/PWMachineGun4.png"
};


PWMachineGun::PWMachineGun(shooting_state_t &sS):
PlayerWeapon(sS, PWMachineGunSprites){
    type=MACHINE_GUN;
    frameTime = MACHINE_GUN_FRAME_TIME;
}


void PWMachineGun::render(int posX, int posY){
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
            gunSounds.playEffect(RIFLE_SHOT, 20);
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


PWMachineGun::~PWMachineGun(){}
