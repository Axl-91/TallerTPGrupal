#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Hud.h"
#include "Install.h"

Hud::Hud():
textureHandler(INSTALLED_TEXTURE_HUD, HUDL, HUDA), 
gun(INSTALLED_TEXTURE_HUD, HGUNL, HGUNA),
numbers(INSTALLED_TEXTURE_HUD, HNUML, HNUMA),
keys(INSTALLED_TEXTURE_HUD, HKEYL,HKEYA),
faces(INSTALLED_TEXTURE_HUD_FACES, HFACEL, HFACEA){
    gun.setPos(posXGun, posYGun);
    numbers.setPos(posXNum, posYNum);
    faces.setPos(posXFac, posYFac);
}

void Hud::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
    gun.setRenderer(renderer);
    numbers.setRenderer(renderer);
    keys.setRenderer(renderer);
    faces.setRenderer(renderer);
}

void Hud::setWeapon(weapon_t aWeapon){
    int srcY = gun.getPosY();
    int srcX = offsetGun*(aWeapon - 1);
    gun.setPos(srcX, srcY);
}

void Hud::renderNumber(int number, int &x, int &y){
    int offsetRenderNum = 8;
    int decimal = 10;
    int srcY = numbers.getPosY();

    while (true){
        int num = number % decimal;

        int srcX = offsetNum * num;
        numbers.setPos(srcX, srcY);
        numbers.render(x, y, HNUML, HNUMA);

        number = number / decimal;
        if (number == 0) return;
        x -= offsetRenderNum;
    }
}

void Hud::renderHealth(int &health){
    int posX = 184;
    int posY = 216;
    renderNumber(health, posX, posY);
    renderFace(health);
}

void Hud::renderFace(const int &health){
    int posX = 136;
    int posY = 204;
    int srcX = faces.getPosX();
    int srcY;
    if (health > 85){
        srcY = (HFACEA+1)*0;
    } else if (health > 70){
        srcY = (HFACEA+1)*1;
    } else if (health > 55){
        srcY = (HFACEA+1)*2;
    } else if (health > 40){
        srcY = (HFACEA+1)*3;
    } else if (health > 25){
        srcY = (HFACEA+1)*4;
    } else if (health > 10){
        srcY = (HFACEA+1)*5;
    } else {
        srcY = (HFACEA+1)*6;
    }
    faces.setPos(srcX, srcY);
    faces.render(posX, posY, HFACEL, HFACEA);
}

void Hud::renderAmmo(const int &ammo){
    int posX = 220;
    int posY = 216;
    renderNumber(ammo, posX, posY);
}

void Hud::renderLife(const int &life){
    int posX = 112;
    int posY = 216;
    renderNumber(life, posX, posY);
}

void Hud::renderScore(const int &score){
    int posX = 82;
    int posY = 216;
    renderNumber(score, posX, posY);
}

void Hud::renderGoldenKey(){
    int keyX = 245;
    int keyY = 41;
    int posX = 240;
    int posY = 205;
    keys.setPos(keyX,keyY);
    keys.render(posX,posY,HKEYL,HKEYA);
}

void Hud::renderSilverKey(){
    int keyX = 254;
    int keyY = 41;
    int posX = 240;
    int posY = 221;
    keys.setPos(keyX,keyY);
    keys.render(posX,posY,HKEYL,HKEYA);
}

void Hud::render(int &longWin, int &highWin){
    int posXGun = 255;
    int posYGun = 210;
    int longTex = longWin-HUDL;
    int highTex = highWin-HUDA;
    textureHandler.render(longTex, highTex, HUDL, HUDA);
    gun.render(posXGun, posYGun, HGUNL, HGUNA);
}

Hud::~Hud(){}
