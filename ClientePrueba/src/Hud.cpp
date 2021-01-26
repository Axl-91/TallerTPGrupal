#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Hud.h"
#include "Install.h"

Hud::Hud():
textureHandler(0, 0, HUDL, HUDA,INSTALLED_TEXTURE_HUD), 
gun(0, 41, HGUNL, HGUNA,INSTALLED_TEXTURE_HUD),
numbers(228, 41, HNUML, HNUMA,INSTALLED_TEXTURE_HUD){}


void Hud::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
    gun.setRenderer(renderer);
    numbers.setRenderer(renderer);
}

void Hud::setWeapon(weapon_t w){
    gun.src.x = offsetGun*(w-1);
}

void Hud::renderNumber(int number, int x, int y){
    while (true){
        int numero = number % 10;

        numbers.src.x = initNum + offsetNum * numero;
        numbers.render(x, y, HNUML, HNUMA);

        number = number / 10;
        if (number == 0) return;
        x -= 8;
    }
}

void Hud::renderHealth(int health){
    renderNumber(health, 184, 216);
}

void Hud::renderAmmo(int ammo){
    renderNumber(ammo, 220, 216);
}

void Hud::renderLife(int life){
    renderNumber(life, 112, 216);
}

void Hud::renderScore(int score){
    renderNumber(score, 82, 216);
}

void Hud::render(int largoWin, int altoWin){
    textureHandler.render(largoWin-HUDL, altoWin-HUDA, HUDL, HUDA);
    gun.render(255, 210, HGUNL, HGUNA);
}

Hud::~Hud(){}
