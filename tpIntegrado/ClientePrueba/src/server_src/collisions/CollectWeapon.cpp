#include <iostream>
#include "CollectWeapon.h"

CollectWeapon::CollectWeapon(int xI, int yI, int cellWidth, int w):
Collectible(xI, yI, cellWidth){
    weapon= (weapon_t) w;
    // xInit=xI*cellWidth+32;
    // xEnd=xInit;
    // yInit=yI*cellWidth+32; 
    // yEnd=yInit;
}

int CollectWeapon::collide(ServerPlayer &p){
    std::cout<<"colision arma"<<std::endl;
    return (int)p.equip(weapon)+WEAPON_OFFSET;
}

CollectWeapon::~CollectWeapon(){}
