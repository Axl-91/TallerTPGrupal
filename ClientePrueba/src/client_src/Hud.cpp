#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Hud.h"
#include "Install.h"

Hud::Hud():
textureHandler(INSTALLED_TEXTURE_HUD, HUDL, HUDA), 
gun(INSTALLED_TEXTURE_HUD, HGUNL, HGUNA),
numbers(INSTALLED_TEXTURE_HUD, HNUML, HNUMA),
keys(INSTALLED_TEXTURE_HUD, HKEYA,HKEYL),
faces(INSTALLED_TEXTURE_HUD_FACES, HFACEL, HFACEA){
    gun.setPos(0, 41);
    numbers.setPos(0, 66);
    faces.setPos(25, 0);
}

void Hud::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
    gun.setRenderer(renderer);
    numbers.setRenderer(renderer);
    keys.setRenderer(renderer);
    faces.setRenderer(renderer);
}

void Hud::setWeapon(weapon_t aWeapon){
    gun.src.x = offsetGun*(aWeapon - 1);
}

void Hud::renderNumber(int number, int x, int y){
    while (true){
        int numero = number % 10;

        numbers.src.x = offsetNum * numero;
        numbers.render(x, y, HNUML, HNUMA);

        number = number / 10;
        if (number == 0) return;
        x -= 8;
    }
}

void Hud::renderHealth(int health){
    renderNumber(health, 184, 216);
    renderFace(health);
}

void Hud::renderFace(int health){
    if (health > 85){
        faces.src.y = (HFACEA+1)*0;
    } else if (health > 70){
        faces.src.y = (HFACEA+1)*1;
    } else if (health > 55){
        faces.src.y = (HFACEA+1)*2;
    } else if (health > 40){
        faces.src.y = (HFACEA+1)*3;
    } else if (health > 25){
        faces.src.y = (HFACEA+1)*4;
    } else if (health > 10){
        faces.src.y = (HFACEA+1)*5;
    } else {
        faces.src.y = (HFACEA+1)*6;
    }
    faces.render(136, 204, HFACEL, HFACEA);
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

void Hud::renderGoldenKey(){
    keys.setPos(245,41);
    keys.render(240,205,HKEYL,HKEYA);
}

void Hud::renderSilverKey(){
    keys.setPos(254,41);
    keys.render(240,221,HKEYL,HKEYA);
}

void Hud::render(int longWin, int highWin){
    textureHandler.render(longWin-HUDL, highWin-HUDA, HUDL, HUDA);
    gun.render(255, 210, HGUNL, HGUNA);
}



Hud::~Hud(){}
