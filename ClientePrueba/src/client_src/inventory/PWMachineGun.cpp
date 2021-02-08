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
}


void PWMachineGun::render(int posX, int posY){
    int delay = 10;
    int frame = 0;


    if (shootingState != SHOOTING_STATE_QUIET && shootingState != SHOOTING_STATE_STOPED){
        numAuxiliar++;
        frame = numAuxiliar/ delay;

         if (frame > 4){
             numAuxiliar = 0;
             frame = 0;
             shootingState=SHOOTING_STATE_QUIET;
        }
    }
    textureHandler.render(96, 72, GUNL, GUNA, frame);

    std::cout<<"render MACHINE GUN"<<std::endl;
}


PWMachineGun::~PWMachineGun(){}
