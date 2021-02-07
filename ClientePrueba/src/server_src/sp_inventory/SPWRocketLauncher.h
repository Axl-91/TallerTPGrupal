#ifndef _PW_ROCKET_LAUNCHER_H_
#define _PW_ROCKET_LAUNCHER_H_


#include "SPWeapon.h"
#include <chrono>

class SPWRocketLauncher: public SPWeapon{
    std::chrono::_V2::system_clock::time_point before;
    std::chrono::_V2::system_clock::time_point now;

public:
    SPWRocketLauncher();
    ~SPWRocketLauncher();
    float shoot(float dist, bool &isShooting) override;
};

#endif
