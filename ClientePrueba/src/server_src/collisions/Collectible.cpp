#include "Collidable.h"
#include "Collectible.h"

Collectible::Collectible(int xI, int yI, int cellWidth){
    xInit=xI*cellWidth+cellWidth/2;
    xEnd=xInit;
    yInit=yI*cellWidth+cellWidth/2; 
    yEnd=yInit;

}

Collectible::~Collectible(){}

bool Collectible::collide(ServerMissile &m){
    return false;
}


bool Collectible::detectCollision(circle &c, float dX,float dY){
    circle aux={c.x+dX, c.y+dY,c.radius};
    return isInside(aux);
}
