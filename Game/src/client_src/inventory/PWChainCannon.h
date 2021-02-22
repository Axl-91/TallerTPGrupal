#ifndef _PW_CHAIN_CANNON_H_
#define _PW_CHAIN_CANNON_H_

#include "PlayerWeapon.h"

class PWChainCannon: public PlayerWeapon{
public:
    PWChainCannon(shooting_state_t &sS);
    ~PWChainCannon();
    void render(int posX, int posY) override;

};

#endif
