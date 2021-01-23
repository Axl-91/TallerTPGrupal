#include "PWKnife.h"

std::vector<std::string> PWKnifeSprites={
    "Media/WeaponSprites/PWKnife0.png",
    "Media/WeaponSprites/PWKnife1.png",
    "Media/WeaponSprites/PWKnife2.png",
    "Media/WeaponSprites/PWKnife3.png",
    "Media/WeaponSprites/PWKnife4.png"
};


PWKnife::PWKnife():
PlayerWeapon(PWKnifeSprites){
    type=KNIFE;
}
PWKnife::~PWKnife(){}
