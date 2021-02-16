#ifndef _MOVABLE_DOOR_H_
#define _MOVABLE_DOOR_H_

#include "Movable.h"
#include "Collidable.h"

class MovableDoor: public Collidable{

public:
    MovableDoor(int xI, int yI, int cellWidth, int wall);
    int collide(ServerPlayer &p) override;
    bool detectCollision(circle &c, float dX,float dY) override;

    ~MovableDoor();
};




#endif
