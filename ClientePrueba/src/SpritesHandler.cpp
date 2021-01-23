#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SpritesHandler.h"

SpritesHandler::SpritesHandler(std::vector<std::string> &iFiles):
imgFiles(iFiles){}

SpritesHandler::~SpritesHandler(){
destroyTextures();
}

void SpritesHandler::destroyTextures(){
    for(size_t i=0; i<texturas.size(); i++){
        SDL_DestroyTexture(texturas[i]);
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
            destroyTextures();
            SDL_FreeSurface(surface);
            throw std::exception(); //Crear excepcion SDL
        }

        texturas.push_back(SDL_CreateTextureFromSurface(rendererWin, surface));
        if (!texturas.back()) {
            destroyTextures();
            SDL_FreeSurface(surface);
            throw std::exception(); //Crear excepcion SDL
        }
        SDL_FreeSurface(surface);
    }
}


void SpritesHandler::render(int posX, int posY, int largo, int alto, int text){
    SDL_Rect rect = {posX, posY, largo, alto};
    SDL_RenderCopy(rendererWin, texturas[text], NULL, &rect);
}

