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

    if (shootingState!=SHOOTING_STATE_QUIET || numAuxiliar!=0){
        if(waited.count()>=frameTime){
            numAuxiliar++;
            before=now;
        }
        frame = numAuxiliar;

         if (frame > 4){
             numAuxiliar = 0;
             frame = 0;
             shootingState=SHOOTING_STATE_QUIET;
        }
    }
    textureHandler.render(96, 72, GUNL, GUNA, frame);
}


PWMachineGun::~PWMachineGun(){}
