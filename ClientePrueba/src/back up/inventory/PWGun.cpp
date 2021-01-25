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
PWGun::~PWGun(){}
