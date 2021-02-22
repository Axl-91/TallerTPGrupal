#ifndef _COLLECT_TREASURE_H_
#define _COLLECT_TREASURE_H_

#include "Collectible.h"
#include "../../common_src/types.h"

class CollectTreasure: public Collectible{
    treasure_t type;
    int points;
public:
    CollectTreasure(int xI, int yI, int cellWidth, int h);
    int collide(ServerPlayer &p) override;

    ~CollectTreasure();
};



#endif
