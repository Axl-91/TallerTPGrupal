#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Walls.h"
#include "Install.h"

Walls::Walls():textureHandler(INSTALLED_TEXTURE_WALLS){}

void Walls::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
}


void Walls::cutFromTexture(int &posX, int &posY, int &length, int &height){
    int x = srcX+posX;
    int y = srcY+posY;
    textureHandler.setSrc(x, y, length, height);
}

void Walls::setWall(int &num){
    int x = ((num%3) * 2) * 64;
    int y = (num/3) * 64;

    srcX = x;
    srcY = y;
    textureHandler.setPos(srcX, srcY);
}

void Walls::setDark(){
    srcX += offset;
    int newSrcX = textureHandler.getPosX() + offset;
    int srcY = textureHandler.getPosY();
    textureHandler.setPos(newSrcX, srcY);
}

void Walls::render(int &posX, int &posY, int &length, int &height){
    textureHandler.render(posX, posY, length, height);
}

Walls::~Walls(){}
