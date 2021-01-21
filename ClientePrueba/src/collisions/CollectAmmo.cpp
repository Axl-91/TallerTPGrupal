#include "CollectAmmo.h"

#define MAP_AMMO 20

CollectAmmo::CollectAmmo(int xI, int yI, int cellWidth, int h){
    ammo=MAP_AMMO;
    xInit=xI*cellWidth+32;
    xEnd=xInit;
    yInit=yI*cellWidth+32; 
    yEnd=yInit;
}

int CollectAmmo::collide(Player &p){
    std::cout<<"colision municion"<<std::endl;

    return (int)p.reload(ammo)+300;
}

// bool CollectWeapon::detectCollision(circle &c, float dX,float dY){
//     circle aux={c.x+dX, c.y+dY,c.radius};
//     return isInside(aux);
// }


CollectAmmo::~CollectAmmo(){}

