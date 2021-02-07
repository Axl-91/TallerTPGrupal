#include <iostream>
#include "SPInventory.h"
#include "SPWKnife.h"
#include "SPWGun.h"
#include "SPWMachineGun.h"
#include "SPWChainCannon.h"
#include "SPWRocketLauncher.h"

#define MAX_AMMO 100

SPInventory::SPInventory(){
    weapons[WP_KNIFE]= new SPWKnife();
    weapons[WP_GUN]= new SPWGun();
    weapons[WP_SECONDARY]= NULL;
}

SPInventory::SPInventory(SPInventory &&other){
    for(int i=1;i<= MAX_WEAPONS ;i++){
        if(other.weapons[i]!=NULL){
            weapons[i] = other.weapons[i];
            other.weapons[i] = NULL;
        }
    }
}

SPInventory::~SPInventory(){
    for(int i=1;i<= MAX_WEAPONS ;i++)
        if(weapons[i]!=NULL){
            delete weapons[i];
            weapons[i]=NULL;
        }
}



SPWeapon* SPInventory::getWeapon(SPWeapon* pw, int i){
    if(weapons[i]!=NULL)
        pw=weapons[i];
    return pw;
}


weapon_t SPInventory::equip(weapon_t w){
    weapon_t last;
    if(weapons[WP_SECONDARY]!=NULL)
        last=weapons[WP_SECONDARY]->getType();
    else
        last=GUN;
    if(last==w)
        return NONE;

    if(w==MACHINE_GUN){
        equipMachineGun();
    }else
    if(w==CHAIN_CANNON){
        equipChainGun();
    }if(w==ROCKET_LAUNCHER){
        equipRocketLauncher();
    }else
        std::cout<<"no equipe nada"<<std::endl;

    return last;
}

weapon_t SPInventory::getSecondaryWPtype(){
    if(weapons[WP_SECONDARY]==NULL)
        return NONE;

    return weapons[WP_SECONDARY]->getType();
}


// bool SPInventory::equip(weapon_t w){
//     weapon_t last;
//     if(weapons[WP_SECONDARY]!=NULL){
//         if(w == (last=weapons[WP_SECONDARY]->getType())){
//             return false;
//         }
//     }

//     if(w==MACHINE_GUN){
//         equipMachineGun();
//     }else if(w==CHAIN_CANNON){
//         equipChainGun();

//     }else if(w==ROCKET_LAUNCHER){
//         equipRocketLauncher();
//     }else
//         return false;

//     return true;
// }





void SPInventory::equipMachineGun(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new SPWMachineGun();
}
void SPInventory::equipChainGun(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new SPWChainCannon();
}
void SPInventory::equipRocketLauncher(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new SPWRocketLauncher();    
}
