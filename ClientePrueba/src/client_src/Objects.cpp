#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "Objects.h"
#include "Install.h"

Objects::Objects(): objHandler(ObjectsSprites){}
void Objects::setRenderer(SDL_Renderer* renderer){
    objHandler.setRenderer(renderer);
}

void Objects::setObject(int num){
    objSelected = num;
}

void Objects::recortar(int x, int y, int largo, int alto){
    objHandler.setSrc(x, y, largo,alto);
}

void Objects::render(int x, int y, int largo, int alto){
    objHandler.render(x, y, largo, alto, objSelected);
}

Objects::~Objects(){}
