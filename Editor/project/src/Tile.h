#ifndef __TILE__
#define __TILE__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int TILE_SIZE = 16;

class Tile{
private:        
	SDL_Rect mBox;
    int type;
public:
    Tile();
    Tile(int,int,int);
    int getX() const;
    int getY() const;
    int getType() const;
    void setType(int);
    bool existPosition(int,int,int,int) const;
    SDL_Rect getBox() const;
    void init();
    ~Tile();
};

#endif