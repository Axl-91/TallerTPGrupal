#include <iostream>
#include "Inventory.h"
#include "PWKnife.h"
#include "PWGun.h"
#include "PWMachineGun.h"
#include "PWChainCanon.h"
#include "PWRocketLauncher.h"

#define MAX_AMMO 100

Inventory::Inventory(){
    ammo=50;
    weapons[WP_KNIFE]= new PWKnife();
    weapons[WP_GUN]= new PWGun();
    weapons[WP_SECONDARY]= new PWRocketLauncher();
}

Inventory::~Inventory(){
    for(int i=1;i<= WEAPONS ;i++)
        if(weapons[i]!=NULL){
            delete weapons[i];
            weapons[i]=NULL;
        }
}

void Inventory::setRenderer(SDL_Renderer* renderer){
    for(int i=1;i<= WEAPONS ;i++)
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


int Inventory::reload(int a){
	if(ammo>=MAX_AMMO)
		return 0;

	std::cout<<"ammo before: "<<ammo<<std::endl;
	ammo+=a;
	if(ammo>MAX_AMMO)
		ammo=MAX_AMMO;

	std::cout<<"ammo after: "<<ammo<<std::endl;

	return 1;
}

int Inventory::getAmmo(){
    return ammo;
}


weapon_t Inventory::equip(weapon_t w){
    weapon_t last;
    if(weapons[WP_SECONDARY]!=NULL)
        last=weapons[WP_SECONDARY]->getType();
    else
        last=GUN;
    if(last==w)
        return NONE;

    if(w==MACHINE_GUN){
        delete weapons[WP_SECONDARY];
        weapons[WP_SECONDARY]= new PWMachineGun();
    }else
    if(w==CHAIN_CANON){
        delete weapons[WP_SECONDARY];
        weapons[WP_SECONDARY]= new PWChainCanon();
    }else
        std::cout<<"no equipe nada"<<std::endl;

   	weapons[WP_SECONDARY]->setRenderer(weaponRenderer);

    return last;
}
