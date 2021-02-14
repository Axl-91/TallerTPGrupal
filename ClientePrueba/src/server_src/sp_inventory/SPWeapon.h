#ifndef _SERVER_PLAYER_WEAPON_H_
#define _SERVER_PLAYER_WEAPON_H_

#include "../../common_src/types.h"
#include <iostream>
#include <chrono>

//Clase padre que se ocupa del manejo de armas y disparo
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