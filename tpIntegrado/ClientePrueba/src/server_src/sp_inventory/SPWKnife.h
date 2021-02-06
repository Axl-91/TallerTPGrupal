#ifndef _SERVER_PLAYER_WEAPON_KNIFE_H_
#define _SERVER_PLAYER_WEAPON_KNIFE_H_

#include "SPWeapon.h"

class SPWKnife: public SPWeapon{
public:
    SPWKnife();
    ~SPWKnife();
    float shoot(float dist, bool &isShooting) override;

};

#endif
