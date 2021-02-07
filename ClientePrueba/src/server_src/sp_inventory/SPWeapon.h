#ifndef _SERVER_PLAYER_WEAPON_H_
#define _SERVER_PLAYER_WEAPON_H_

#include "../../common_src/types.h"
#include <iostream>

#define KNIFE_ATTACK_RANGE 16

#define KNIFE_DAMAGE 10
#define GUN_DAMAGE 10
#define MACHINE_GUN_DAMAGE 2
#define CHAIN_CANNON_DAMAGE 10
#define ROCKET_LAUNCHER_DAMAGE 50


#define MACHINE_GUN_BULLET_COUNTER 5 

#define KNIFE_WAIT_TIME 500 //ms
#define GUN_WAIT_TIME 500 //ms

#define MACHINE_GUN_BULLET_WAIT_TIME 40 //ms
#define MACHINE_GUN_WAIT_TIME 1000 //ms
#define CHAIN_CANNON_WAIT_TIME 100 //ms
#define ROCKET_LAUNCHE_WAIT_TIME 1000 //ms


#include <chrono>

class SPWeapon{
protected:
    int damage;
    bool estaDisparando = false;
    weapon_t type;
    bool shooting;
    std::chrono::_V2::system_clock::time_point before;
    std::chrono::_V2::system_clock::time_point now;

    // void disparar();
public:
    void shootingTrue();
    virtual float shoot(float dist, shooting_state_t &shootingState) = 0;
    SPWeapon();
	SPWeapon(const SPWeapon &copy) = delete;
//	PlayerWeapon operator=(const PlayerWeapon &copy) = delete;
    bool estaEnAccion();
    weapon_t getType();
    ~SPWeapon();
};

#endif