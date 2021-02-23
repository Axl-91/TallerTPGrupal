#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "Collidable.h"


class Movable: public Collidable{
private:
public:
    Movable();
    ~Movable();
    bool collide(ServerMissile &m) override;
};

#endif