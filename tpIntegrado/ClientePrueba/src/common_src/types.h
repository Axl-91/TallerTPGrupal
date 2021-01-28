#ifndef TYPES__H
#define TYPES__H

#define MAX_WEAPONS 3
#define MAX_HEALTH 100
#define MAX_AMMO 100

typedef enum{
    WP_KNIFE = 1,
    WP_GUN = 2,
    WP_SECONDARY = 3
}player_weapons_t;

typedef enum{
    NO_EVENT,
    PLAYER_SET_WEAPON_KNIFE,
    PLAYER_SET_WEAPON_GUN,
    PLAYER_SET_WEAPON_SECONDARY,
    PLAYER_START_MOVING_FORWARD,
    PLAYER_START_MOVING_BACKWARD,
    PLAYER_STOP_MOVING,
    PLAYER_START_ROTATING_RIGHT,
    PLAYER_START_ROTATING_LEFT,
    PLAYER_STOP_ROTATING,
    PLAYER_SHOOT,
    PLAYER_STOP_SHOOTING,
    GAME_QUIT,
    PICHIWAR,
    UNIRME
}event_t;

typedef enum{
    NONE = 0,
    KNIFE = 1,
    GUN = 2,
    MACHINE_GUN = 3,
    CHAIN_CANNON = 4,
    ROCKET_LAUNCHER = 5
}weapon_t;

typedef struct{
    size_t tag;
    int step;
    float x;
    float y;
    float dirx;
    float diry;
    float ang;
    weapon_t secondaryWP;
    player_weapons_t currentWP;
    size_t ammo;
    bool key;
    bool shooting;
    int health;
    size_t score;
    size_t lifes;
}Player_t;

typedef enum{
    BLOOD = 17,
    FOOD = 3,
    MEDICAL_EQUIPMENT = 4
}heal_t;

typedef struct{
    int x;
    int y;
    int value;
    bool changeAvailable;
}Map_change_t;

#define PI 3.14159265358979323846

#endif