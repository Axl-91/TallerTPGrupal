#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SpritesHandler.h"

SpritesHandler::SpritesHandler(std::string file, int lenght, int height){
    imgFiles = {file};
    src = {0, 0, lenght, height};
}

SpritesHandler::SpritesHandler(std::vector<std::string> &iFiles, int lenght, int height)
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

            // destroyTextures();
            SDL_FreeSurface(surface);
            throw std::exception(); //Crear excepcion SDL
        }
        texturesVector.push_back(SDL_CreateTextureFromSurface(rendererWin, surface));
        if (!texturesVector.back()) {
            // destroyTextures();
            SDL_FreeSurface(surface);
            throw std::exception(); //Crear excepcion SDL
        }
        SDL_FreeSurface(surface);
    }
}

void SpritesHandler::setSrc(int posX, int posY, int lenght, int height){
    src = {posX, posY, lenght, height};
}

void SpritesHandler::setPos(int posX, int posY){
    src.x = posX;
    src.y = posY;
}

void SpritesHandler::setSize(int lenght, int height){
    src.h = height;
    src.w = lenght;
}

void SpritesHandler::render(int posX, int posY, int lenght, int height, int type){
    SDL_Rect rect = {posX, posY, lenght, height};
    SDL_RenderCopy(rendererWin, texturesVector[type], &src, &rect);
}

void SpritesHandler::render(int posX, int posY, int lenght, int height){
    SDL_Rect rect = {posX, posY, lenght, height};
    SDL_RenderCopy(rendererWin, texturesVector[0], &src, &rect);
}
