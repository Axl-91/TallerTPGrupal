#ifndef _PW_ROCKET_LAUNCHER_H_
#define _PW_ROCKET_LAUNCHER_H_


#include "SPWeapon.h"
#include <chrono>

class SPWRocketLauncher: public SPWeapon{
public:
    SPWRocketLauncher();
    ~SPWRocketLauncher();
//    float shoot(float dist, shooting_state_t &shootingState) override;
  	float shoot(shooting_state_t &shootingState, bool &shootMissile) override;

};

#endif
