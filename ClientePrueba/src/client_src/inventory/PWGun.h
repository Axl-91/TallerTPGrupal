#ifndef _PW_GUN_H_
#define _PW_GUN_H_

#include "PlayerWeapon.h"

class PWGun: public PlayerWeapon{
public:
    PWGun(shooting_state_t &sS);
    ~PWGun();
    void render(int largoWin, int altoWin) override;
};

#endif
