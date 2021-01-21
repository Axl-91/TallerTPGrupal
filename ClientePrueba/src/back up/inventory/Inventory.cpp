#include <iostream>
#include "Inventory.h"
#include "PWKnife.h"
#include "PWGun.h"
#include "PWMachineGun.h"
#include "PWChainCanon.h"

Inventory::Inventory(){
    weapons[WP_KNIFE]= new PWKnife();
    weapons[WP_GUN]= new PWGun();
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


weapon_t Inventory::equip(weapon_t w){
    weapon_t last;
    if(weapons[WP_SECONDARY]!=NULL)
        last=weapons[WP_SECONDARY]->getType();
    else
        last=NONE;
    if(last==w)
        return last;

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
