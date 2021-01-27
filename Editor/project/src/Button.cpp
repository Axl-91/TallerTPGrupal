#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Button.h"

Button::Button(){}

void Button::setRenderer(SDL_Renderer* renderer){
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
    SDL_Rect but = {x, y, BUTH, BUTW};    
    SDL_RenderCopy(winRenderer, textura, NULL, &but);     
}

void Button::avanzar(){	
	y -= 40;
}

void Button::retroceder(){	
    movs++;
	y += 40;
}

void Button::pollEvent(SDL_Event &evento){    	
    if (evento.type == SDL_KEYDOWN){
		switch(evento.key.keysym.sym){
			case SDLK_UP:
				avanzar();
				break;
			case SDLK_DOWN:
				retroceder();
				break;
			break;
		}
	}
}

Button::~Button(){
    SDL_DestroyTexture(textura);
}