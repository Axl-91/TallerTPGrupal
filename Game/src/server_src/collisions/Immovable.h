#ifndef _IMMOVABLE_H_
#define _IMMOVABLE_H_

#include "Collidable.h"


class Immovable: public Collidable{
private:
    /* data */
public:
    Immovable(/* args */);
    ~Immovable();
    bool collide(ServerMissile &m) override;

};

#endif
