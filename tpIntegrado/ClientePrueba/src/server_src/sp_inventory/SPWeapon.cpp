#include <iostream>
#include <unistd.h>
#include "SPWeapon.h"



SPWeapon::SPWeapon(){
    shooting=false;
}


bool SPWeapon::estaEnAccion(){
    return estaDisparando;
}

// void SPWeapon::shoot(){
//     estaDisparando=true;
// }

void SPWeapon::shootingTrue(){
    shooting=true;
}


weapon_t SPWeapon::getType(){
    return type;
}

SPWeapon::~SPWeapon(){}
