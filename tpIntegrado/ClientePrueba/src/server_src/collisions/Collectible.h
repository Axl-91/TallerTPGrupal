#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "Collidable.h"

class Collectible: public Collidable{
private:
    /* data */
public:
    Collectible(/* args */);
    // int collide(Player &p) override;
    bool detectCollision(circle &c, float dX,float dY) override;

    ~Collectible();
};



#endif
