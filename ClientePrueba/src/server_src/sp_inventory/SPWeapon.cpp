#include <iostream>
#include <unistd.h>
#include "SPWeapon.h"

SPWeapon::SPWeapon(){
    shooting=false;
}


bool SPWeapon::estaEnAccion(){
    return estaDisparando;
}

int SPWeapon::getUsedBullets(){
    return usedBullets;
}

void SPWeapon::shootingTrue(){
    shooting=true;
}


weapon_t SPWeapon::getType(){
    return type;
}

SPWeapon::~SPWeapon(){}
