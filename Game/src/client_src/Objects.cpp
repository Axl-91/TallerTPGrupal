#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <unistd.h>
#include "Objects.h"

Objects::Objects():
    objectsFiles(fileObj),
    objectsSprites(objectsFiles.getVectorFiles()),
    objHandler(objectsSprites)
{}

void Objects::setRenderer(SDL_Renderer* renderer){
    objHandler.setRenderer(renderer);
}

void Objects::setObject(int &num){
    objSelected = num;
}

void Objects::cutFromTexture(int &x, int &y, const int &length, const int &height){
    objHandler.setSrc(x, y, length,height);
}

void Objects::render(int &x, int &y, const int &length, const int &height){
    objHandler.render(x, y, length, height, objSelected);
}

Objects::~Objects(){}
