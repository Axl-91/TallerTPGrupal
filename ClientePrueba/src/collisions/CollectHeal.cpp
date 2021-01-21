#include "CollectHeal.h"

CollectHeal::CollectHeal(int xI, int yI, int cellWidth, int h){
    // weapon= (weapon_t) w;
    type=(heal_t) h;

    if(type==BLOOD)
        heal=1;
    else if(type==FOOD)
        heal=10;
    else if(type==MEDICAL_EQUIPMENT)
        heal=20;
    else 
        heal=0;

    xInit=xI*cellWidth+32;
    xEnd=xInit;
    yInit=yI*cellWidth+32; 
    yEnd=yInit;
}

int CollectHeal::collide(Player &p){
    std::cout<<"colision cura"<<std::endl;

    return (int)p.heal(heal)+200;
}

// bool CollectWeapon::detectCollision(circle &c, float dX,float dY){
//     circle aux={c.x+dX, c.y+dY,c.radius};
//     return isInside(aux);
// }


CollectHeal::~CollectHeal(){}

