#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Point.h"

Point::Point(int x, int y){
    xMouse = x;
    yMouse = y;
}

Point::Point(){ }

Point::~Point(){}