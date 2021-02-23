#ifndef AILUA__H
#define AILUA__H

#include <iostream>
#include <map>
#include <vector>


#include "../common_src/types.h"
#include "../common_src/Circle.h"
#include "ShootingRaycaster.h"
// #include "svRaycaster.h"
// #include "svMap.h"
#include "CollisionMap.h"
#include "AILuaScript.h"

#define SHOOTING_SIZE 100
#define COEF_SHOOTING_DISTANCE_DIVISOR 512
#define COEF_SHOOTING_DISTANCE_OFFSET 0.2
#define COEF_SHOOTING_ANGLE_DIVISOR 96
#define LONG_SCREEN 320

class AILua {
private:
    int decision;
    circle position;
    float ang;
    float dx;
    float dy;
    float step;
    int health;
    size_t lifes;
    size_t score;
    // Map &mapPlayer;
    size_t ID;
    shooting_state_t shootingState;
    player_weapons_t currentWeapon;
    weapon_t secondaryWeapon;
    std::map<size_t, Player_t> enemies;
    void updateEnemy(Player_t &p);
    void updatePlayerInfo(Player_t &aPlayerInfo);
    void getDamageCoefficient(Player_t &enemy, float &coef, float wallDist);
    void renderRaycaster();
    bool checkForEnemiesInSight(event_t &event, Vector &aux);
    std::vector<Player_t> orderEnemies(Vector &pos);
    bool objIsVisible(Vector &pos);
    void changeToAttackMode();
    bool attackModeOn;
    void follow(event_t &event, float &relativeAng, float &distProyPlane);
    bool rotating;
    void noEnemyAtSight(event_t &event);
    bool moving;
    float distBuffer[320];
    // svMap mapPlayer;
    CollisionMap mapPlayer;
    AILuaScript lua;
public:
    AILua(float x, float y, float ang, size_t ID, std::vector<std::vector<int>> &lvl);
    void setID(size_t anID);
    void update(Player_t &p);
    void makeDecision(event_t &event);
    void setGameMap(std::vector<std::vector<int> > &aVector);
    // void sendMapUpdate(Map_change_t &aMapChange);
};

#endif
