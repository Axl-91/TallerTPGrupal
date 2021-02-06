#ifndef _SERVER_PLAYER_WEAPON_MACHINE_GUN_H_
#define _SERVER_PLAYER_WEAPON_MACHINE_GUN_H_

#include "SPWeapon.h"

class SPWMachineGun: public SPWeapon{
public:
    SPWMachineGun();
    ~SPWMachineGun();
    float shoot(float dist, bool &isShooting) override;
};

#endif
