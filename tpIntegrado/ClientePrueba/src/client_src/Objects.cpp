#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "Objects.h"
#include "Install.h"

Objects::Objects():textureHandler(srcX, srcY, LADO, LADO,INSTALLED_TEXTURE_OBJECTS){}

void Objects::setRenderer(SDL_Renderer* renderer){
    textureHandler.setRenderer(renderer);
}

void Objects::setObject(int num){
    int limite = 5;
    int x = (num % limite) * offset;
    int y = (num / limite) * offset;
    srcX = x;
    srcY = y;
    textureHandler.src.x = srcX;
    textureHandler.src.y = srcY;
}

void Objects::recortar(int x, int y, int largo, int alto){
    textureHandler.setSrc(srcX+x, srcY+y, largo, alto);
}

void Objects::render(int x, int y, int largo, int alto){
    textureHandler.render(x, y, largo, alto);
}

Objects::~Objects(){}
