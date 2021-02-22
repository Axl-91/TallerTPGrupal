#ifndef _MOVABLE_DOOR_H_
#define _MOVABLE_DOOR_H_

#include "Movable.h"
#include "Collidable.h"

class MovableDoor: public Movable{
    door_type_t type;
public:
    MovableDoor(int xI, int yI, int cellWidth, int type);
    int collide(ServerPlayer &p) override;
    bool detectCollision(circle &c, float dX,float dY) override;

    ~MovableDoor();
};




#endif
