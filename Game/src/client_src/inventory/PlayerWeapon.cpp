#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(shooting_state_t &sS, std::vector<std::string> &imgs):
shootingState(sS),
textureHandler(imgs){
    before = std::chrono::high_resolution_clock::now();
    offset = SDL_RENDER_WEAPON_OFFSET;
    frameAuxiliar = 0;
    posXWeapon = SDL_RENDER_WEAPON_POS_X;
    posYWeapon = SDL_RENDER_WEAPON_POS_Y;
}

void PlayerWeapon::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
}

bool PlayerWeapon::estaEnAccion(){
    if(shootingState!=SHOOTING_STATE_QUIET)
        return true;

    return false;
}

void PlayerWeapon::shoot(shooting_state_t sS){
    shootingState = sS;
}


weapon_t PlayerWeapon::getType(){
    return type;
}

PlayerWeapon::~PlayerWeapon(){}
