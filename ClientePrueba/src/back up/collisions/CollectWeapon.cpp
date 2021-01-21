#include <iostream>
#include "CollectWeapon.h"

CollectWeapon::CollectWeapon(int xI, int yI, int cellWidth, int w){
    weapon= (weapon_t) w;
    xInit=xI*cellWidth+32;
    xEnd=xInit;
    yInit=yI*cellWidth+32; 
    yEnd=yInit;
}

int CollectWeapon::collide(Player &p){
    std::cout<<"colision arma"<<std::endl;
    return (int)p.equip(weapon)+100;
}

// bool CollectWeapon::detectCollision(circle &c, float dX,float dY){
//     circle aux={c.x+dX, c.y+dY,c.radius};
//     return isInside(aux);
// }


CollectWeapon::~CollectWeapon(){}

