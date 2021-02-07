#ifndef _PW_KNIFE_H_
#define _PW_KNIFE_H_

#include "PlayerWeapon.h"

class PWKnife: public PlayerWeapon{
public:
    PWKnife();
    ~PWKnife();
    void render(int posX, int posY) override;
};

#endif
