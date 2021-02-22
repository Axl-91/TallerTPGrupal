#ifndef _PW_MACHINE_GUN_H_
#define _PW_MACHINE_GUN_H_

#include "PlayerWeapon.h"

class PWMachineGun: public PlayerWeapon{
public:
    PWMachineGun(shooting_state_t &sS);
    ~PWMachineGun();
    void render(int posX, int posY) override;

};

#endif
