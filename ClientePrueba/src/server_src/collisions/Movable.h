#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "Collidable.h"


class Movable: public Collidable{
private:
    /* data */
public:
    Movable(/* args */);
    ~Movable();
    bool collide(ServerMissile &m) override;
};

#endif