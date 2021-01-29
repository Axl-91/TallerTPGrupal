#ifndef __POINT__
#define __POINT__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class Position{
private:        
    int x;      
    int y;
public:    
    void init(int x, int y);
    int getPosX() const;
    int getPosY() const;
    void setPosX(int x);
    void setPosY(int y);
    bool samePos(Position &pos);
    Position();
    ~Position();
};

#endif