#ifndef _IMMOVABLE_OBJECT_H_
#define _IMMOVABLE_OBJECT_H_

#include "Immovable.h"
// #include "Collidable.h"

class ImmovableObject: public Immovable{

public:
    ImmovableObject(int xI, int yI, int cellWidth, int wall);
    int collide(ServerPlayer &p) override;
    bool detectCollision(circle &c, float dX,float dY) override;

    ~ImmovableObject();
};




#endif
