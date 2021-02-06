#ifndef _SERVER_PLAYER_WEAPON_H_
#define _SERVER_PLAYER_WEAPON_H_

#include "../../common_src/types.h"
#include <iostream>

class SPWeapon{
protected:
    bool estaDisparando = false;
    weapon_t type;

    void disparar();
public:

    virtual void shoot() = 0;
    SPWeapon();
	SPWeapon(const SPWeapon &copy) = delete;
//	PlayerWeapon operator=(const PlayerWeapon &copy) = delete;
    bool estaEnAccion();
    weapon_t getType();
    ~SPWeapon();
};

#endif