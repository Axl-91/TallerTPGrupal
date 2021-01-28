#ifndef SERVERPLAYER__T
#define SERVERPLAYER__T

#include "../common_src/Circle.h"
#include <cmath>
#include "../common_src/types.h"

typedef enum{
    FORWARD = 1,
    BACKWARD =-1,
    MOVE_QUIET = 0
}player_move_orientation_t;

typedef enum{
    LEFT = 1,
    RIGHT =-1,
    ROTATE_QUIET = 0
}player_rotate_orientation_t;


class ServerPlayer{
private:
    circle position;
    player_move_orientation_t moveOrientation;
    player_rotate_orientation_t rotateOrientation;
    float ang;
    float dirx;
    float diry;
    float step;
    int health;
    size_t ID;
    size_t lifes;
    size_t score;
    weapon_t secondaryWP;
    player_weapons_t currentWP;
    size_t ammo;
    bool key;
    bool shooting;


public:
    ServerPlayer(float x, float y, float a);
    ~ServerPlayer();
    void move();
    void rotate();

    void getPlayerInfo(Player_t &p);
    void getPosition(float &x, float &y);
    void getPosition(circle &c);
    void getDirection(float &x, float &y);
    void setDirection(float x, float y);
    void setMoveOrientation(player_move_orientation_t o);
    void seteRotateOrientation(player_rotate_orientation_t o);
    player_move_orientation_t getMoveOrientation();

    void setCurrentWeapon(player_weapons_t aWeapon);
    void startShooting();
    void stopShooting();
    weapon_t equip(weapon_t weapon);
    int heal(int h);
    int reload(int ammo);
};

#endif