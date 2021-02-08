#include "Tile.h"

Tile::Tile(){}

Tile::Tile(int _x, int _y,int _type){
    mBox.x = _x;
    mBox.y = _y;    
    mBox.w = TILE_SIZE;
    mBox.h = TILE_SIZE;    
    type = _type;    
}

bool Tile::existPosition(int x, int y,int offsetX,int offsety) const{
    if((x>=mBox.x +offsetX) && (mBox.x+TILE_SIZE +offsetX>=x)){
        if((y>=mBox.y+offsety) && (mBox.y+TILE_SIZE+offsety >=y)){
            return true;            
        }
    }
    return false;
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

void Tile::setType(int _type){
    type = _type;
}

Tile::~Tile(){}
