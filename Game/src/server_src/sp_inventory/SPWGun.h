#ifndef _SERVER_PLAYER_WEAPON_GUN_H_
#define _SERVER_PLAYER_WEAPON_GUN_H_

#include "SPWeapon.h"
#include <iostream>

class SPWGun: public SPWeapon{
public:
    SPWGun();
    ~SPWGun();
//    float shoot(float dist, shooting_state_t &shootingState) override;
  	float shoot(shooting_state_t &shootingState, bool &shootMissile) override;

};

#endif
