#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Hud.h"
#include "Install.h"

Hud::Hud():
textureHandler(0, 0, HUDL, HUDA,INSTALLED_TEXTURE_HUD), 
gun(0, 42, HGUNL, HGUNA,INSTALLED_TEXTURE_HUD){}


void Hud::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
    gun.setRenderer(renderer);
}

void Hud::setWeapon(weapon_t w){
    gun.src.x = offsetGun*(w-1);
}

void Hud::render(int largoWin, int altoWin){
    textureHandler.render(largoWin-HUDL, altoWin-HUDA, HUDL, HUDA);
    gun.render(255, 210, HGUNL, HGUNA);
}

Hud::~Hud(){}
