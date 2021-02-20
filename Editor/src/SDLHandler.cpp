#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDLHandler.h"


SDLHandler::SDLHandler(int posX, int posY, int length, int width, std::string iFile):
imgFile(iFile){
    texture==NULL;
    src = {posX, posY, length, width};
}

SDLHandler::~SDLHandler(){    
    SDL_DestroyTexture(texture);     
    texture==NULL;
    rendererWin = NULL;     
}

void SDLHandler::setRenderer(SDL_Renderer* renderer){
    rendererWin = renderer;
    getTexture();
}

void SDLHandler::getTexture(){
    SDL_Surface* surface = IMG_Load(imgFile.data());
    if (!surface) {
        SDL_FreeSurface(surface);
        throw std::exception(); 
    }

    auto color = SDL_MapRGB(surface->format, 152, 0, 136);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    texture = SDL_CreateTextureFromSurface(rendererWin, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        throw std::exception(); //Crear excepcion SDL
    }
    SDL_FreeSurface(surface);
}


void SDLHandler::render(int posX, int posY, int lenght, int high){
    SDL_Rect rect = {posX, posY, lenght, high};
    SDL_RenderCopy(rendererWin, texture, &src, &rect);
}


void SDLHandler::setSrc(int posX, int posY, int lenght, int high){
    src = {posX, posY, lenght, high};
}

