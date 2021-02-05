#ifndef __TILE__
#define __TILE__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Position.h"

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
    void render( SDL_Rect& camera, SDL_Rect& gTileClips );
    SDL_Rect getBox() const;
    void init();
    ~Tile();
};

#endif