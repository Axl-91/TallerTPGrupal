#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SpritesHandler.h"

SpritesHandler::SpritesHandler(const std::string &file, const int &lenght, const int &height){
    imgFiles = {file};
    src = {0, 0, lenght, height};
}

SpritesHandler::SpritesHandler(std::vector<std::string> &iFiles, const int &lenght, const int &height)
    :imgFiles(iFiles){
        src = {0, 0, lenght, height};
}

SpritesHandler::~SpritesHandler(){
    destroyTextures();
}

void SpritesHandler::destroyTextures(){
    for(size_t i=0; i<texturesVector.size(); i++){
        SDL_DestroyTexture(texturesVector[i]);
    }
}

void SpritesHandler::setRenderer(SDL_Renderer* renderer){
    rendererWin = renderer;
    getTextures(renderer);
}

void SpritesHandler::getTextures(SDL_Renderer* renderer){
    for(size_t i=0; i<imgFiles.size(); i++){
        SDL_Surface* surface = IMG_Load(imgFiles[i].data());
        if (!surface) {
            SDL_FreeSurface(surface);
            throw std::exception(); //Crear excepcion SDL
        }
        texturesVector.push_back(SDL_CreateTextureFromSurface(rendererWin, surface));
        if (!texturesVector.back()) {
            SDL_FreeSurface(surface);
            throw std::exception(); //Crear excepcion SDL
        }
        SDL_FreeSurface(surface);
    }
}

void SpritesHandler::setSrc(int &posX, int &posY, const int &lenght, const int &height){
    src = {posX, posY, lenght, height};
}

int SpritesHandler::getPosX(){
    return src.x;
}

int SpritesHandler::getPosY(){
    return src.y;
}

void SpritesHandler::setPos(int &posX, int &posY){
    src.x = posX;
    src.y = posY;
}

void SpritesHandler::setSize(int &lenght, int &height){
    src.h = height;
    src.w = lenght;
}

void SpritesHandler::render(int &posX, int &posY, const int &lenght, const int &height, const int &type){
    SDL_Rect rect = {posX, posY, lenght, height};
    SDL_RenderCopy(rendererWin, texturesVector[type], &src, &rect);
}

void SpritesHandler::render(int &posX, int &posY, const int &lenght, const int &height){
    SDL_Rect rect = {posX, posY, lenght, height};
    SDL_RenderCopy(rendererWin, texturesVector[0], &src, &rect);
}
