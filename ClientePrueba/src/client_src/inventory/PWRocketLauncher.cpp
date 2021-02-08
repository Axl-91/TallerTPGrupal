#include "PWRocketLauncher.h"
#include <iostream>
std::vector<std::string> PWRocketLauncherSprites={
    "Media/WeaponSprites/PWRocketLauncher0.png",
    "Media/WeaponSprites/PWRocketLauncher1.png",
    "Media/WeaponSprites/PWRocketLauncher2.png",
    "Media/WeaponSprites/PWRocketLauncher3.png",
    "Media/WeaponSprites/PWRocketLauncher4.png"
};


PWRocketLauncher::PWRocketLauncher(shooting_state_t &sS):
PlayerWeapon(sS, PWRocketLauncherSprites){
    type=ROCKET_LAUNCHER;
}

void PWRocketLauncher::render(int posX, int posY){
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

    // std::cout<<"render ROCKET LAUNCHER"<<std::endl;
}



PWRocketLauncher::~PWRocketLauncher(){}