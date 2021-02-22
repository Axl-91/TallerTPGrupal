#include "Collidable.h"
#include "Movable.h"

Movable::Movable(/* args */){
}


Movable::~Movable(){
}

bool Movable::collide(ServerMissile &m){
    return false;
}
