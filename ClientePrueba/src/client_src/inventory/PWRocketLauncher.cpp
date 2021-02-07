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
    type=ROCKET_LAUNCHER;
}

void PWRocketLauncher::render(int posX, int posY){
    std::cout<<"render ROCKET LAUNCHER"<<std::endl;
}



PWRocketLauncher::~PWRocketLauncher(){}