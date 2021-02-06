#include "Tile.h"

Tile::Tile(){}

Tile::Tile(int _x, int _y,int _type){
    mBox.x = _x;
    mBox.y = _y;    
    mBox.w = 32;
    mBox.h = 32;    
    type = _type;    
}

int Tile::getX() const{
    return mBox.x;    
}
SDL_Rect Tile::getBox() const{
    return mBox;    
} 

int Tile::getY() const{
    return mBox.y;    
}

int Tile::getType() const{
    return type;    
}

Tile::~Tile(){}
