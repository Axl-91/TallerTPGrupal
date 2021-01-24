#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "Walls.h"
#include "Install.h"

Walls::Walls():textureHandler(srcX, srcY, offset, offset,INSTALLED_TEXTURE_WALLS){}

void Walls::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
}


void Walls::recortar(int &posX, int &posY, int &largo, int &alto){
    int x = srcX+posX;
    int y = srcY+posY;
    textureHandler.setSrc(x, y, largo, alto);
}

void Walls::setWall(int &num){
    int x = ((num%3) * 2) * 64;
    int y = (num/3) * 64;

    srcX = x;
    srcY = y;
    textureHandler.src.x = srcX;
    textureHandler.src.y = srcY;
}

void Walls::setDark(){
    srcX += offset;
    textureHandler.src.x += offset;
}

void Walls::render(int &posX, int &posY, int &largo, int &alto){
    textureHandler.render(posX, posY, largo, alto);
}

Walls::~Walls(){}
