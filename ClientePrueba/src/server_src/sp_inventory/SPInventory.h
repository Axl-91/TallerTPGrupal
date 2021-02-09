#ifndef _SERVER_INVENTORY_H_
#define _SERVER_INVENTORY_H_

#include <map>
#include "SPWeapon.h"
#include "../../common_src/types.h"


//
//Clase que se ocupa del manejo de las armas equipadas
//
class SPInventory{
    std::map<int,SPWeapon*> weapons;
    
public:
    SPInventory();
    SPInventory(SPInventory &&other);
    ~SPInventory();
    weapon_t equip(weapon_t w);

    void equipMachineGun();
    void equipChainGun();
    void equipRocketLauncher();
    weapon_t getSecondaryWPtype();

    SPWeapon* getWeapon(SPWeapon* pw, int i);
};

#endif
