#ifndef _MOVABLE_FALSE_WALL_H_
#define _MOVABLE_FALSE_WALL_H_

#include "Movable.h"
#include "Collidable.h"

class MovableFalseWall: public Movable{

public:
    MovableFalseWall(int xI, int yI, int cellWidth, int type);
    int collide(ServerPlayer &p) override;
    bool detectCollision(circle &c, float dX,float dY) override;

    ~MovableFalseWall();
};




#endif
