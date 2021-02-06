#ifndef _SERVER_INVENTORY_H_
#define _SERVER_INVENTORY_H_

#include <map>
#include "SPWeapon.h"
#include "../../common_src/types.h"





class SPInventory{
    std::map<int,SPWeapon*> weapons;
    
    // int ammo;
    // bool key;
public:
    SPInventory();
    ~SPInventory();
    weapon_t equip(weapon_t w);

    // bool equip(weapon_t w);
    // int reload(int a);
    //int getAmmo();
    //void setAmmo(int a);
    void equipMachineGun();
    void equipChainGun();
    void equipRocketLauncher();
    weapon_t getSecondaryWPtype();

    SPWeapon* getWeapon(SPWeapon* pw, int i);
};

#endif
