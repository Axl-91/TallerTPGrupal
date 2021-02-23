#include "Collidable.h"
#include "Movable.h"

Movable::Movable(){
}


Movable::~Movable(){
}

bool Movable::collide(ServerMissile &m){
    return false;
}
