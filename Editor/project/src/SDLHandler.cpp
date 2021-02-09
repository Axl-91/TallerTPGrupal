#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "SDLHandler.h"


SDLHandler::SDLHandler(int posX, int posY, int length, int width, std::string iFile):
imgFile(iFile){
    textura==NULL;
    src = {posX, posY, length, width};
}

SDLHandler::~SDLHandler(){
     if(textura!=NULL)
         SDL_DestroyTexture(textura);
}


void SDLHandler::setRenderer(SDL_Renderer* renderer){
    rendererWin = renderer;
    getTexture();
}

void SDLHandler::getTexture(){
    SDL_Surface* surface = IMG_Load(imgFile.data());
    if (!surface) {
        throw std::exception(); 
    }

    auto color = SDL_MapRGB(surface->format, 255, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    textura = SDL_CreateTextureFromSurface(rendererWin, surface);
    if (!textura) {
        throw std::exception(); //Crear excepcion SDL
    }
    SDL_FreeSurface(surface);
}


void SDLHandler::render(int posX, int posY, int largo, int alto){
    SDL_Rect rect = {posX, posY, largo, alto};
    SDL_RenderCopy(rendererWin, textura, &src, &rect);
}


void SDLHandler::setSrc(int posX, int posY, int largo, int alto){
    src = {posX, posY, largo, alto};
}

