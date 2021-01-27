#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Arrow.h"

Arrow::Arrow(){
    imgFile = "arrow.png";
    movs = 0;
    x = posxInicial = 0;
    y = posyInicial = 150;
}

Arrow::~Arrow(){}