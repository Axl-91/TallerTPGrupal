#ifndef _COLLECT_HEAL_H_
#define _COLLECT_HEAL_H_

#include "Collectible.h"
#include "../../common_src/types.h"

class CollectHeal: public Collectible{
    heal_t type;
    int heal;
public:
    CollectHeal(int xI, int yI, int cellWidth, int h);
    int collide(ServerPlayer &p) override;

    ~CollectHeal();
};



#endif
