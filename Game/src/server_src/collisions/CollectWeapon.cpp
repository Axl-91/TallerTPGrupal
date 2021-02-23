#include <iostream>
#include "CollectWeapon.h"

CollectWeapon::CollectWeapon(int xI, int yI, int cellWidth, int w):
Collectible(xI, yI, cellWidth){
    weapon= (weapon_t) w;
}

int CollectWeapon::collide(ServerPlayer &p){
    return (int)p.equip(weapon)+WEAPON_OFFSET;
}

CollectWeapon::~CollectWeapon(){}

