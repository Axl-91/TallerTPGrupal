#include <iostream>
#include "SPInventory.h"
#include "SPWKnife.h"
#include "SPWGun.h"
#include "SPWMachineGun.h"
#include "SPWChainCannon.h"
#include "SPWRocketLauncher.h"

#define MAX_AMMO 100

//
//El jugador empieza con cuchillo y pistola equipados en el inventario
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

//
//selecciona arma equipada para cambiarla por la actual
SPWeapon* SPInventory::getWeapon(SPWeapon* pw, int i){
    if(weapons[i]!=NULL)
        pw=weapons[i];
    return pw;
}

//
//Equipa arma secundaria y devuelve un enum con el arma anterior para que se actualice el mapa
//Si ya la tenia no equipa nada: devuelve GUN
//Si no tenia arma, la equipa y devuelve NONE
//Si tenia otra arma, la equipa  y devuelve un enum con el arma secundaria anterior
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
