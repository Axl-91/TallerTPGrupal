#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "PlayerWeapon.h"
#include "../Install.h"

PlayerWeapon::PlayerWeapon(int xI, int yI, int xE, int yE):
textureHandler(xI, yI, xE, yE, INSTALLED_TEXTURE_GUNS){}

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
        int frame = numAuxiliar/offset;
        textureHandler.src.x = offset*frame;
        numAuxiliar++;
        if (frame > 4){
            numAuxiliar = 0;
            textureHandler.src.x = 0;
            estaDisparando = false;
        }
    }
    textureHandler.render(96, 72, GUNL, GUNA);
}


weapon_t PlayerWeapon::getType(){
    return type;
}

PlayerWeapon::~PlayerWeapon(){}
