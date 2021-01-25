#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include <map>
#include "PlayerWeapon.h"
#include "../weapon_t.h"

#define WEAPONS 3

#define WP_KNIFE 1
#define WP_GUN 2
#define WP_SECONDARY 3


class Inventory{
    std::map<int,PlayerWeapon*> weapons;
    SDL_Renderer *weaponRenderer;
    int ammo;
    bool key;
public:
    Inventory();
    ~Inventory();
    weapon_t equip(weapon_t w);
    int reload(int a);
    int getAmmo();

    PlayerWeapon* getWeapon(PlayerWeapon* pw, int i);
    void setRenderer(SDL_Renderer* renderer);
};

#endif
