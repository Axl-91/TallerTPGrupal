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
    frameTime = ROCKET_LAUNCHER_FRAME_TIME;
}

void PWRocketLauncher::render(int posX, int posY){
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
    textureHandler.render(posXWeapon, posYWeapon, GUNL, GUNA, frame);
}



PWRocketLauncher::~PWRocketLauncher(){}