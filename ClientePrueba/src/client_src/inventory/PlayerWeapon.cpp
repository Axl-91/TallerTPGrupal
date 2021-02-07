#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "PlayerWeapon.h"
#include "../Install.h"

PlayerWeapon::PlayerWeapon(std::vector<std::string> &imgs):
textureHandler(imgs){}

void PlayerWeapon::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
}

bool PlayerWeapon::estaEnAccion(){
    if(shootingState!=SHOOTING_STATE_QUIET)
        return true;

    return false;
}

void PlayerWeapon::shoot(){
    shootingState = SHOOTING_STATE_STARTED;
}

// void PlayerWeapon::render(int largoWin, int altoWin){
//     int delay = 10;
//     int frame = 0;

//     if (shootingState!=SHOOTING_STATE_QUIET){
//         numAuxiliar++;
//         frame = numAuxiliar/ delay;

//          if (frame > 4){
//              numAuxiliar = 0;
//              frame = 0;
//              shootingState!=SHOOTING_STATE_QUIET;
//         }
//     }
//     textureHandler.render(96, 72, GUNL, GUNA, frame);
// }

weapon_t PlayerWeapon::getType(){
    return type;
}

PlayerWeapon::~PlayerWeapon(){}
