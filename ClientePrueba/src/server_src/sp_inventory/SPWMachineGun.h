#ifndef _SERVER_PLAYER_WEAPON_MACHINE_GUN_H_
#define _SERVER_PLAYER_WEAPON_MACHINE_GUN_H_

#include <chrono>
#include "SPWeapon.h"

class SPWMachineGun: public SPWeapon{
    int bulletsCounter;    
public:
    SPWMachineGun();
    ~SPWMachineGun();
    float shoot(float dist, shooting_state_t &shootingState) override;
};

#endif
