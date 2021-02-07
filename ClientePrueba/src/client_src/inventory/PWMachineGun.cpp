#include "PWMachineGun.h"

std::vector<std::string> PWMachineGunSprites={
    "Media/WeaponSprites/PWMachineGun0.png",
    "Media/WeaponSprites/PWMachineGun1.png",
    "Media/WeaponSprites/PWMachineGun2.png",
    "Media/WeaponSprites/PWMachineGun3.png",
    "Media/WeaponSprites/PWMachineGun4.png"
};


PWMachineGun::PWMachineGun():
PlayerWeapon(PWMachineGunSprites){
    type=MACHINE_GUN;
}


void PWMachineGun::render(int posX, int posY){
    std::cout<<"render MACHINE GUN"<<std::endl;
}


PWMachineGun::~PWMachineGun(){}
