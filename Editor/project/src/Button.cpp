#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Button.h"

Button::Button(){}

void Button::init(SDL_Renderer* renderer){
    winRenderer = renderer;
    getTexture();
}

void Button::getTexture(){
    SDL_Surface* surface = IMG_Load(imgFile);
    if (!surface) {
        throw std::exception(); 
    }
    auto color = SDL_MapRGB(surface->format, 152, 0, 136);
    SDL_SetColorKey(surface, SDL_TRUE, color);

    textura = SDL_CreateTextureFromSurface(winRenderer, surface);
    if (!textura) {
        throw std::exception(); 
    }
    SDL_FreeSurface(surface);    
}

void Button::render(int largoWin, int altoWin){    
    SDL_Rect but = {pos.getPosX(), pos.getPosY(), h, w};    
    SDL_RenderCopy(winRenderer, textura, NULL, &but);     
}

Position Button::getPosition()const{
    return pos;
}

void Button::setSrc(int _x, int _y, int _w, int _h){
    pos.setPosX(_x);
    pos.setPosY(_y);
    w = _w;
    h = _h;    
}

Button::~Button(){
    SDL_DestroyTexture(textura);
}