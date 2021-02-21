#ifndef _SERVER_PLAYER_WEAPON_CHAIN_CANNON_H_
#define _SERVER_PLAYER_WEAPON_CHAIN_CANNON_H_

#include "SPWeapon.h"
class SPWChainCannon: public SPWeapon{

public:
    SPWChainCannon();
    ~SPWChainCannon();
  //  float shoot(float dist, shooting_state_t &shootingState) override;
   	float shoot(shooting_state_t &shootingState, bool &shootMissile) override;
};

#endif
