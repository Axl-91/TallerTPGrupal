#include "PWKnife.h"

std::vector<std::string> PWKnifeSprites={
    "Media/WeaponSprites/PWKnife0.png",
    "Media/WeaponSprites/PWKnife1.png",
    "Media/WeaponSprites/PWKnife2.png",
    "Media/WeaponSprites/PWKnife3.png",
    "Media/WeaponSprites/PWKnife4.png"
};


PWKnife::PWKnife(shooting_state_t &sS):
PlayerWeapon(sS, PWKnifeSprites){
    type=KNIFE;
}

void PWKnife::render(int largoWin, int altoWin){
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
}


PWKnife::~PWKnife(){}
