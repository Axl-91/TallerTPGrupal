#include <iostream>
#include "Inventory.h"
#include "PWKnife.h"
#include "PWGun.h"
#include "PWMachineGun.h"
#include "PWChainCannon.h"
#include "PWRocketLauncher.h"

Inventory::Inventory(shooting_state_t &sS):
shootingState(sS){
    weapons[WP_KNIFE]= new PWKnife(sS);
    weapons[WP_GUN]= new PWGun(sS);
    weapons[WP_SECONDARY]= NULL;
    weaponRenderer = NULL;
}

Inventory::~Inventory(){
    for(int i=1;i<= MAX_WEAPONS ;i++)
        if(weapons[i]!=NULL){
            delete weapons[i];
            weapons[i]=NULL;
        }
}

void Inventory::setRenderer(SDL_Renderer* renderer){
    for(int i=1;i<= MAX_WEAPONS ;i++)
        if(weapons[i]!=NULL){
        	weapons[i]->setRenderer(renderer);
        }
    weaponRenderer=renderer;
}


PlayerWeapon* Inventory::getWeapon(PlayerWeapon* pw, int i){
    if(weapons[i]!=NULL)
        pw=weapons[i];
    return pw;
}

bool Inventory::equip(weapon_t w){
    weapon_t last;

    if(w == NONE){
        if(weapons[WP_SECONDARY]!=NULL){
            delete weapons[WP_SECONDARY];
            weapons[WP_SECONDARY]=NULL;
        }
        return false;
    }

    if(weapons[WP_SECONDARY]!=NULL){
        if(w == weapons[WP_SECONDARY]->getType()){
            return false;
        }
    }
    
    if(w==MACHINE_GUN){
        equipMachineGun();
    }else if(w==CHAIN_CANNON){
        equipChainGun();

    }else if(w==ROCKET_LAUNCHER){
        equipRocketLauncher();
    }else
        return false;

    if(weaponRenderer!=NULL)
       	weapons[WP_SECONDARY]->setRenderer(weaponRenderer);

    return true;
}

void Inventory::equipMachineGun(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new PWMachineGun(shootingState);
}

void Inventory::equipChainGun(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new PWChainCannon(shootingState);
}
void Inventory::equipRocketLauncher(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new PWRocketLauncher(shootingState);    
}
