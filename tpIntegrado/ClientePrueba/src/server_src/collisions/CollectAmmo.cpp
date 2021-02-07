#include "CollectAmmo.h"

#define MAP_AMMO 20

CollectAmmo::CollectAmmo(int xI, int yI, int cellWidth, int h):
Collectible(xI, yI, cellWidth){
    ammo=MAP_AMMO;
    // xInit=xI*cellWidth+32;
    // xEnd=xInit;
    // yInit=yI*cellWidth+32; 
    // yEnd=yInit;
}

int CollectAmmo::collide(ServerPlayer &p){
    std::cout<<"colision municion"<<std::endl;

    return (int)p.reload(ammo)+AMMO_OFFSET;
}

CollectAmmo::~CollectAmmo(){}
