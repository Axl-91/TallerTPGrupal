#ifndef _COLLECT_WEAPON_H_
#define _COLLECT_WEAPON_H_

#include "Collectible.h"
#include "../../common_src/types.h"

class CollectWeapon: public Collectible{
    weapon_t weapon;
public:
    CollectWeapon(int xI, int yI, int cellWidth, int w);
    int collide(ServerPlayer &p) override;
    // bool detectCollision(circle &c, float dX,float dY) override;

    ~CollectWeapon();
};

#endif
