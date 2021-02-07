#ifndef _SERVER_PLAYER_WEAPON_CHAIN_CANNON_H_
#define _SERVER_PLAYER_WEAPON_CHAIN_CANNON_H_

#include "SPWeapon.h"
#include <chrono>
class SPWChainCannon: public SPWeapon{
    std::chrono::_V2::system_clock::time_point before;
    std::chrono::_V2::system_clock::time_point now;

public:
    SPWChainCannon();
    ~SPWChainCannon();
    float shoot(float dist, bool &isShooting) override;
};

#endif
