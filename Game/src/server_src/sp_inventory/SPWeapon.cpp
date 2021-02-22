#include <iostream>
#include <unistd.h>
#include "SPWeapon.h"

SPWeapon::SPWeapon(){
    shooting = false;
    shooted = false;
}


bool SPWeapon::estaEnAccion(){
    return estaDisparando;
}

int SPWeapon::getBulletsNeeded(){
    return usedBullets;
}


int SPWeapon::getUsedBullets(){
    if(shooted == true)
        return usedBullets;
    return 0;
}

void SPWeapon::shootingTrue(){
    shooting=true;
}


weapon_t SPWeapon::getType(){
    return type;
}

SPWeapon::~SPWeapon(){}
