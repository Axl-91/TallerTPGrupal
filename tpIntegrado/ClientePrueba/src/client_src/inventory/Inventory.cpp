#include <iostream>
#include "Inventory.h"
#include "PWKnife.h"
#include "PWGun.h"
#include "PWMachineGun.h"
#include "PWChainCannon.h"
#include "PWRocketLauncher.h"

#define MAX_AMMO 100

Inventory::Inventory(){
    ammo=50;
    weapons[WP_KNIFE]= new PWKnife();
    weapons[WP_GUN]= new PWGun();
    weapons[WP_SECONDARY]= NULL;
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


// int Inventory::reload(int a){
// 	if(ammo>=MAX_AMMO)
// 		return 0;

// 	std::cout<<"ammo before: "<<ammo<<std::endl;
// 	ammo+=a;
// 	if(ammo>MAX_AMMO)
// 		ammo=MAX_AMMO;

// 	std::cout<<"ammo after: "<<ammo<<std::endl;

// 	return 1;
// }

int Inventory::getAmmo(){
    return ammo;
}

void Inventory::setAmmo(int a){
    ammo = a;
}

bool Inventory::equip(weapon_t w){
    weapon_t last;
    if(weapons[WP_SECONDARY]!=NULL){
        if(w == weapons[WP_SECONDARY]->getType()){
            return false;
        }
    }
    
    if(w==MACHINE_GUN){
        equipMachineGun();
    }else if(w==CHAIN_CANNON){
        equipChainGun();

    // }else if(w==ROCKET_LAUNCHER){
    //     equipRocketLauncher();
    }else
        return false;
   	weapons[WP_SECONDARY]->setRenderer(weaponRenderer);

    return true;
}

void Inventory::equipMachineGun(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new PWMachineGun();
}
void Inventory::equipChainGun(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new PWChainCannon();
}
void Inventory::equipRocketLauncher(){
    delete weapons[WP_SECONDARY];
    weapons[WP_SECONDARY]= new PWRocketLauncher();    
}
