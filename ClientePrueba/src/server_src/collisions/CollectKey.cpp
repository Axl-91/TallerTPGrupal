#include "CollectKey.h"


CollectKey::CollectKey(int xI, int yI, int cellWidth, int k):
Collectible(xI, yI, cellWidth){
    type=(game_key_t) k;

    // xInit=xI*cellWidth+32;
    // xEnd=xInit;
    // yInit=yI*cellWidth+32; 
    // yEnd=yInit;
}

int CollectKey::collide(ServerPlayer &p){
    std::cout<<"colision cura"<<std::endl;

    return (int)p.grabKey(type)+KEY_OFFSET;
}

// bool CollectWeapon::detectCollision(circle &c, float dX,float dY){
//     circle aux={c.x+dX, c.y+dY,c.radius};
//     return isInside(aux);
// }


CollectKey::~CollectKey(){}

