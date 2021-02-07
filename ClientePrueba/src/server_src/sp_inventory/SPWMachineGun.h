#ifndef _SERVER_PLAYER_WEAPON_MACHINE_GUN_H_
#define _SERVER_PLAYER_WEAPON_MACHINE_GUN_H_

#include <chrono>
#include "SPWeapon.h"

class SPWMachineGun: public SPWeapon{
    int bulletsCounter;
    std::chrono::_V2::system_clock::time_point before;
    std::chrono::_V2::system_clock::time_point now;
    
public:
    SPWMachineGun();
    ~SPWMachineGun();
    float shoot(float dist, bool &isShooting) override;
};

#endif
