#ifndef _COLLECT_HEAL_H_
#define _COLLECT_HEAL_H_

#include "Collectible.h"
// #include "../weapon_t.h"
class CollectHeal: public Collectible{
    // weapon_t weapon;
public:
    CollectHeal(int xI, int yI, int cellWidth, int h);
    // int collide(Player &p) override;
    bool detectCollision(circle &c, float dX,float dY) override;

    ~CollectHeal();
};



#endif
