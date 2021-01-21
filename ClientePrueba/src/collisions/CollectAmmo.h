#ifndef _COLLECT_AMMO_H_
#define _COLLECT_AMMO_H_

#include "Collectible.h"
class CollectAmmo: public Collectible{
    int ammo;
public:
    CollectAmmo(int xI, int yI, int cellWidth, int h);
    int collide(Player &p) override;

    ~CollectAmmo();
};



#endif
