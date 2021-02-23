#ifndef SERVERPLAYER__T
#define SERVERPLAYER__T

#include <cmath>
#include <chrono>
#include "../common_src/types.h"
#include "../common_src/Vector.h"
#include "sp_inventory/SPWeapon.h"
#include "sp_inventory/SPInventory.h"

#define PLAYER_STEP 3



//
//Clase que se ocupa de la logica del jugador
class ServerPlayer{
private:
    std::chrono::_V2::system_clock::time_point timeOfDead;
    std::chrono::_V2::system_clock::time_point now;

    float init_posx;
    float init_posy;

    circle position;
    player_move_orientation_t moveOrientation;
    player_rotate_orientation_t rotateOrientation;
    SPInventory inventory;
	SPWeapon *currentWeapon;

    float ang;
    float dirx;
    float diry;
    float step;
    size_t ID;
    size_t lifes;
    size_t score;
    player_weapons_t currentWP;
    int health;

    size_t ammo;
    bool blueKey;
    bool goldKey;   
    shooting_state_t shootingState;
    bool lost;
    bool dead;

    bool openingDoor;
    bool updateAvailable;
    weapon_t getSecondaryWPtype();

public:
    ServerPlayer(float x, float y, float a, size_t ID);
    ~ServerPlayer();

    bool hasGoldKey();
    bool hasBlueKey();
    void usedGoldKey();
    void usedBlueKey();

    void startOpenDoor();
    void stopOpenDoor();
    bool isOpeningDoor();

    void respawn();
    bool updateIsAvailable();
    void updated();

    ServerPlayer(ServerPlayer&& other);
    void rotate();

    void getDamageCoefficient(ServerPlayer &enemy, float &coef, float wallDist);
    float getAngle();
    int shoot(bool &shootMissile);

    void beDamaged(int damage);

    bool isDead();
    bool tryToRespawn();

    player_move_orientation_t getMoveOrientation();
    void getPlayerInfo(Player_t &p);
    void getPosition(float &x, float &y);
    void getPosition(circle &c);
    void getDirection(float &x, float &y);
    void setDirection(float x, float y);
    void setMoveOrientation(player_move_orientation_t o);
    void seteRotateOrientation(player_rotate_orientation_t o);
    float getDist(ServerPlayer &enemy);

    void move();
    void setCurrentWeapon(player_weapons_t aWeapon);
    void startShooting();
    void stopShooting();
    bool isShooting();
    weapon_t equip(weapon_t weapon);
    int heal(int h);
    int reload(int ammo);
    int grabKey(game_key_t k);
    int addPoints(int p);
    float getRadius();
    size_t getID();
};

#endif