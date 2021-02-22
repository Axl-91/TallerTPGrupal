#ifndef _COLLECT_KEY_H_
#define _COLLECT_KEY_H_

#include "Collectible.h"
#include "../../common_src/types.h"

class CollectKey: public Collectible{
    game_key_t type;
public:
    CollectKey(int xI, int yI, int cellWidth, int k);
    int collide(ServerPlayer &p) override;

    ~CollectKey();
};



#endif
