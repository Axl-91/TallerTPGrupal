#include "PWRocketLauncher.h"
#include <iostream>
std::vector<std::string> PWRocketLauncherSprites={
    "Media/WeaponSprites/PWRocketLauncher0.png",
    "Media/WeaponSprites/PWRocketLauncher1.png",
    "Media/WeaponSprites/PWRocketLauncher2.png",
    "Media/WeaponSprites/PWRocketLauncher3.png",
    "Media/WeaponSprites/PWRocketLauncher4.png"
};


PWRocketLauncher::PWRocketLauncher():
PlayerWeapon(PWRocketLauncherSprites){
    std::cout << "Falta sprite, se usa el de machine gun" << std::endl;
    type=MACHINE_GUN;
}

PWRocketLauncher::~PWRocketLauncher(){}