#ifndef _PW_MACHINE_GUN_H_
#define _PW_MACHINE_GUN_H_

#include "PlayerWeapon.h"

class PWMachineGun: public PlayerWeapon{
public:
    PWMachineGun();
    ~PWMachineGun();
    void render(int posX, int posY) override;

};

#endif
