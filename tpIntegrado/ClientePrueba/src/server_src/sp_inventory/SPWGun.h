#ifndef _SERVER_PLAYER_WEAPON_GUN_H_
#define _SERVER_PLAYER_WEAPON_GUN_H_

#include "SPWeapon.h"
#include <iostream>

class SPWGun: public SPWeapon{
public:
    SPWGun();
    ~SPWGun();
    void shoot() override;
};

#endif
