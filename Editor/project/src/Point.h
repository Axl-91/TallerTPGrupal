#ifndef __POINT__
#define __POINT__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class Point{
private:        
    int xMouse;
    int yMouse;      
public:
    Point(int x, int y);
    Point();
    ~Point();
};

#endif