#ifndef _IMMOVABLE_WALL_H_
#define _IMMOVABLE_WALL_H_

#include "Immovable.h"
// #include "Collidable.h"

class ImmovableWall: public Immovable{

public:
    ImmovableWall(int xI, int yI, int cellWidth, int wall);
    int collide(ServerPlayer &p) override;
    bool detectCollision(circle &c, float dX,float dY) override;

    ~ImmovableWall();
};




#endif
