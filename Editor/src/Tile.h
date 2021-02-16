#ifndef __TILE__
#define __TILE__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

const int TILE_SIZE = 16;
const int TILE_OPTION = 64;

class Tile{
private:        
	SDL_Rect mBox;
    int type;
    int fil;
    int col;
public:
    Tile();
    Tile(int,int,int,int,int);
    Tile(int _x, int _y,int _type,int _fil, int _col,int w, int h);
    int getX() const;
    int getY() const;
    int getfil() const;
    int getcol() const;
    int getType() const;
    int getFacty() const;
    int getFactx() const;
    void setType(int);
    bool existPosition(int,int,int,int) const;
    bool existbyFilCol(int,int) const;
    SDL_Rect getBox() const;
    void init();
    ~Tile();
};

#endif