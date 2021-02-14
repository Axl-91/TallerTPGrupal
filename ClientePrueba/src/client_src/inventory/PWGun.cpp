#include "PWGun.h"

std::vector<std::string> PWGunSprites={
    "Media/WeaponSprites/PWGun0.png",
    "Media/WeaponSprites/PWGun1.png",
    "Media/WeaponSprites/PWGun2.png",
    "Media/WeaponSprites/PWGun3.png",
    "Media/WeaponSprites/PWGun4.png"
};

PWGun::PWGun(shooting_state_t &sS):
PlayerWeapon(sS, PWGunSprites){
    type=GUN;
}


void PWGun::render(int largoWin, int altoWin){
    int delay = 2;
    int frame = 0;


    // if (shootingState!=SHOOTING_STATE_QUIET){
    //     frame=0;
    // }else
    std::cout<<"shootingState: "<<shootingState<<std::endl;
    if (shootingState!=SHOOTING_STATE_QUIET){
        numAuxiliar++;
        frame = numAuxiliar/ delay;

         if (frame > 4){
             numAuxiliar = 0;
             frame = 0;
             shootingState=SHOOTING_STATE_QUIET;
        }
    }
    // if(shootingState==SHOOTING_STATE_QUIET)
    //     frame=0;
    
    // if(shootingState==SHOOTING_STATE_STARTED)
    //     frame=1;

    // if(shootingState==SHOOTING_STATE_SHOOTING)
    //     frame=2;

    // if(shootingState==SHOOTING_STATE_WAITING)
    //     frame=3;

    // if(shootingState==SHOOTING_STATE_STOPED)
    //     frame=4;

    textureHandler.render(96, 72, GUNL, GUNA, frame);
}


PWGun::~PWGun(){}
