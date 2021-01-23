#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "PlayerWeapon.h"
#include "../Install.h"

// std::vector<std::string> imgs1=
//     {"WEAPONS/PWKnife0.png",
//     "WEAPONS/PWKnife1.png",
//     "WEAPONS/PWKnife2.png",
//     "WEAPONS/PWKnife3.png",
//     "WEAPONS/PWKnife4.png"};

// PlayerWeapon::PlayerWeapon(int xI, int yI, int xE, int yE):
// // textureHandler(xI, yI, xE, yE, INSTALLED_TEXTURE_GUNS),
// textureHandler(imgs1){}


PlayerWeapon::PlayerWeapon(std::vector<std::string> &imgs):
textureHandler(imgs){}



void PlayerWeapon::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
}

bool PlayerWeapon::estaEnAccion(){
    return estaDisparando;
}

void PlayerWeapon::shoot(){
    estaDisparando=true;
}


void PlayerWeapon::render(int largoWin, int altoWin){
   
    if (estaDisparando){
        numAuxiliar++;
         if (numAuxiliar > 4){
             numAuxiliar = 0;
             estaDisparando = false;
        }
    }
    textureHandler.render(96, 72, GUNL, GUNA, numAuxiliar);
}


weapon_t PlayerWeapon::getType(){
    return type;
}

PlayerWeapon::~PlayerWeapon(){}
