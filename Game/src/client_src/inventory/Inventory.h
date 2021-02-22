#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <map>
#include "PlayerWeapon.h"
#include "../../common_src/types.h"





class Inventory{
    std::map<int,PlayerWeapon*> weapons;
    SDL_Renderer *weaponRenderer;
    shooting_state_t &shootingState;
public:
    Inventory(shooting_state_t &sS);
    ~Inventory();
    bool equip(weapon_t w);
    void equipMachineGun();
    void equipChainGun();
    void equipRocketLauncher();

    PlayerWeapon* getWeapon(PlayerWeapon* pw, int i);
    void setRenderer(SDL_Renderer* renderer);
};

#endif
