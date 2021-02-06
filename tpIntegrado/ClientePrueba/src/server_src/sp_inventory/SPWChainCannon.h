#ifndef _SERVER_PLAYER_WEAPON_CHAIN_CANNON_H_
#define _SERVER_PLAYER_WEAPON_CHAIN_CANNON_H_

#include "SPWeapon.h"

class SPWChainCannon: public SPWeapon{
public:
    SPWChainCannon();
    ~SPWChainCannon();
    float shoot(float dist, bool &isShooting) override;
};

#endif
