#ifndef AILUA__H
#define AILUA__H

#include <map>
#include <vector>

#include "../common_src/types.h"

class AILua {
private:
    int decision;
    circle position;
    float angulo;
    float dx;
    float dy;
    float step;
    // float distBuffer[320];
    int health;
    size_t lifes;
    size_t score;
    // Map &mapPlayer;
    size_t ID;
    shooting_state_t shootingState;
	// PlayerWeapon *currentWeapon;
    player_weapons_t currentWeapon;
    weapon_t secondaryWeapon;
    std::map<size_t, Player_t> enemies;
    // anEnemyArreglo;
   void updateEnemy(Player_t &p);
   void updatePlayerInfo(Player_t &aPlayerInfo);
 
public:
    AILua(float x, float y, float ang, size_t ID);
    void setID(size_t anID);
    void update(Player_t &p);
    void makeDecision(event_t &event);
    void setGameMap(std::vector<std::vector<int>> &aVector);
    // void sendMapUpdate(Map_change_t &aMapChange);
};

#endif
