#include "Collidable.h"
#include "Collectible.h"

Collectible::Collectible(/* args */){}
Collectible::~Collectible(){}

bool Collectible::detectCollision(circle &c, float dX,float dY){
    circle aux={c.x+dX, c.y+dY,c.radius};
    return isInside(aux);
}
