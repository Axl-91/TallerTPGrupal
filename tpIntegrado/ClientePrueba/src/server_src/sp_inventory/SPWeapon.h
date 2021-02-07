#ifndef _SERVER_PLAYER_WEAPON_H_
#define _SERVER_PLAYER_WEAPON_H_

#include "../../common_src/types.h"
#include <iostream>

#define KNIFE_ATTACK_TIME 1
#define GUN_ATTACK_TIME 2
#define MACHINE_GUN_ATTACK_TIME 3
#define CHAIN_CANNON_ATTACK_TIME 4


class SPWeapon{
protected:
    bool estaDisparando = false;
    weapon_t type;
    bool shooting;
    // void disparar();
public:
    void shootingTrue();
    virtual float shoot(float dist, bool &isShooting) = 0;
    SPWeapon();
	SPWeapon(const SPWeapon &copy) = delete;
//	PlayerWeapon operator=(const PlayerWeapon &copy) = delete;
    bool estaEnAccion();
    weapon_t getType();
    ~SPWeapon();
};

#endif