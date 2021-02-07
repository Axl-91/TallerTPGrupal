#ifndef _PW_ROCKET_LAUNCHER_H_
#define _PW_ROCKET_LAUNCHER_H_


#include "PlayerWeapon.h"

class PWRocketLauncher: public PlayerWeapon{
public:
    PWRocketLauncher();
    ~PWRocketLauncher();
    void render(int posX, int posY) override;
};

#endif
