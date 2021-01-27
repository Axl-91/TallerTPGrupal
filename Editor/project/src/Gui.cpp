#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Gui.h"

Gui::Gui(){}

void Gui::init(SDL_Renderer* renderer){
    rendererWin = renderer;
    getTexture();
}

void Gui::setSrc(int posX, int posY, int largo, int alto){
    src = {posX, posY, largo, alto};
}

Gui::~Gui(){}