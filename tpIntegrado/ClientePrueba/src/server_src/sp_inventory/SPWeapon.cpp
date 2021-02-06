#include <iostream>
#include <unistd.h>
#include "SPWeapon.h"


SPWeapon::SPWeapon(){}


bool SPWeapon::estaEnAccion(){
    return estaDisparando;
}

// void SPWeapon::shoot(){
//     estaDisparando=true;
// }

weapon_t SPWeapon::getType(){
    return type;
}

SPWeapon::~SPWeapon(){}
