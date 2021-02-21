#ifndef _COLLECTIBLE_H_
#define _COLLECTIBLE_H_

#include "Collidable.h"

class Collectible: public Collidable{
private:
    /* data */
public:
    Collectible(int xI, int yI, int cellWidth);
    bool detectCollision(circle &c, float dX,float dY) override;
    bool collide(ServerMissile &m) override;

    ~Collectible();
};



#endif
