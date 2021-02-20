#ifndef TYPES__H
#define TYPES__H
#include <iostream>
#include "Vector.h"

#define MAX_WEAPONS 3
#define MAX_HEALTH 100
#define MAX_AMMO 100
#define PI 3.14159265358979323846

/***************************************************************************/
//
//                          WEAPON STATS
//
/***************************************************************************/
#define KNIFE_ATTACK_RANGE 16

#define KNIFE_DAMAGE 10
#define GUN_DAMAGE 10
#define MACHINE_GUN_DAMAGE 2
#define CHAIN_CANNON_DAMAGE 5
#define ROCKET_LAUNCHER_DAMAGE 50


#define MACHINE_GUN_BULLET_COUNTER 5 

#define KNIFE_WAIT_TIME 500 //ms
#define GUN_WAIT_TIME 500 //ms

#define MACHINE_GUN_BULLET_WAIT_TIME 40 //ms
#define MACHINE_GUN_WAIT_TIME 1000 //ms
#define CHAIN_CANNON_WAIT_TIME 100 //ms
#define ROCKET_LAUNCHER_WAIT_TIME 1000 //ms

/***************************************************************************/
//
//                          WEAPON FRAME TIMES
//
/***************************************************************************/
#define KNIFE_FRAME_TIME 40 //ms
#define GUN_FRAME_TIME 40 //ms
#define MACHINE_GUN_FRAME_TIME 33 //ms
#define CHAIN_CANNON_FRAME_TIME 33 //ms
#define ROCKET_LAUNCHER_FRAME_TIME 40 //ms


/***************************************************************************/
//
//                          COLLIDABLE OFFSETS
//
/***************************************************************************/
#define COLLIDABLE_OFFSET 100
#define COLLECTIBLE_OFFSET 10
#define KEY_OFFSET 100
#define HEAL_OFFSET 110
#define AMMO_OFFSET 120
#define WEAPON_OFFSET 130
#define TREASURE_OFFSET 140
#define IMMOVABLE_OBJECT_OFFSET 200
#define MOVABLE_DOOR_OFFSET 300

#define WALL_OFFSET 400


/***************************************************************************/
//
//                          ITEM STATS
//
/***************************************************************************/
#define MAP_AMMO 5

#define TREASURE_POINTS_CROSS 100
#define TREASURE_POINTS_CALIZ 100
#define TREASURE_POINTS_CHEST 100
#define TREASURE_POINTS_CROWN 100

#define HEAL_BLOOD 1
#define HEAL_FOOD 10
#define HEAL_MEDICAL_EQUIPMENT 20
////////////////////////////////////////////////////////////////////////////////////
typedef enum{
    WP_KNIFE = 1,
    WP_GUN = 2,
    WP_SECONDARY = 3
}player_weapons_t;

typedef enum{
    TAG_NO_UPDATE,
    TAG_GAME_QUIT,
    TAG_PLAYER_INFO,
    TAG_MAP_CHANGE,
    TAG_MAP_INIT,
    TAG_MATCH_LIST,
    TAG_MAP_LIST,
    TAG_NAME_NOT_AVAILABLE
}update_tag_t;

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
    NEW_MATCH,
    NEW_NAME,
    GET_MATCHES,
    GET_MAPS,
    SET_MAP,
    START_GAME,
    JOIN,
    PLAYER_START_OPENING_DOOR,
    PLAYER_STOP_OPENING_DOOR
}event_t;
 

typedef enum{
    SHOOTING_STATE_QUIET = 0,
    SHOOTING_STATE_STARTED = 1,
    SHOOTING_STATE_SHOOTING = 2,
}shooting_state_t;

typedef enum{
    BLOOD = 1,
    FOOD = 2,
    MEDICAL_EQUIPMENT = 3
}heal_t;

typedef enum{
    KEY_GOLD = 1,
    KEY_BLUE = 2
}game_key_t;

typedef enum{
    CROSS = 1,
    CALIZ = 2,
    CHEST = 3,
    CROWN = 4
}treasure_t;

typedef enum{
    NONE = 0,
    KNIFE = 1,
    GUN = 2,
    MACHINE_GUN = 3,
    CHAIN_CANNON = 4,
    ROCKET_LAUNCHER = 5
}weapon_t;

typedef enum{
    HOUND = 1,
    GUARD = 2,
    SS = 3,
    OFFICIAL = 4,
    MUTANT = 5
}enemy_type_t;

typedef enum{
    NO_KEY_DOOR = 50,
    BLUE_KEY_DOOR = 52,
    GOLD_KEY_DOOR = 53
}door_type_t;

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

typedef struct{
    event_t event;
    std::string info;
}menu_event_t;

typedef struct{
    size_t ID;
    int step;
    float x;
    float y;
    float dirx;
    float diry;
    float ang;
    weapon_t secondaryWP;
    player_weapons_t currentWP;
    size_t ammo;
    bool blueKey;
    bool goldKey;
    shooting_state_t shootingState;
    player_move_orientation_t moving;
    player_rotate_orientation_t rotating;
    int health;
    size_t score;
    size_t lifes;
}Player_t;

typedef struct{
    Player_t playerInfo;
    int moving_frame;
    int shooting_frame;
    enemy_type_t type;
    bool dead;
    int dead_frame;
}Enemy_t;


typedef struct{
    Vector pos;
    int doorType;
    bool needBlueKey;
    bool needGoldKey;
}Door_t;

typedef struct{
    int x;
    int y;
    int value;
}Map_change_t;

typedef struct{
    size_t ID;
    int step;
    float x;
    float y;
    float dirx;
    float diry;
    int damage;
}Misil_t;

typedef struct{
    Player_t playerUpdate;
    Map_change_t mapChange;
    bool mapChangeAvailable;
}Update_t;


typedef struct {
    event_t event;
    size_t playerTag;
}MatchEvent_t;


#endif