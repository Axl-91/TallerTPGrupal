#include "Collidable.h"
#include "Immovable.h"

Immovable::Immovable(/* args */){
}
Immovable::~Immovable(){
}

bool Immovable::collide(ServerMissile &m){
    return true;
}
