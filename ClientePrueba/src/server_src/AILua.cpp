#include "AILua.h"

AILua::AILua(float x, float y, float ang, size_t anID){
    position.x=x;
    position.y=y;
    position.radius=16;
    angulo=ang;
    ID=anID;
}

void AILua::update(Player_t &p){
    if(p.ID == ID){
        updatePlayerInfo(p);
    } else {
        updateEnemy(p);
    }
}


void AILua::setID(size_t anID){
    ID = anID;
}
void AILua::updatePlayerInfo(Player_t &p){
        position.x = p.x;
        position.y = p.y;
        angulo = p.ang;
        lifes = p.lifes;
        score = p.score;
        // inventory.setAmmo(p.ammo);
        health = p.health;
        currentWeapon = p.currentWP;
        secondaryWeapon = p.secondaryWP;
        shootingState=p.shootingState;
}

void AILua::updateEnemy(Player_t &p){
    enemies[p.ID] = p;
}

void AILua::setGameMap(std::vector<std::vector<int>> &aVector){

}

void AILua::makeDecision(event_t &event){
    switch(decision){
    case 1:
        event = PLAYER_START_ROTATING_LEFT;
        decision++;
        break;
    case 0:
        event = PLAYER_START_MOVING_FORWARD;
        decision++;
        break;
    case 2:
        event = PLAYER_START_ROTATING_RIGHT;
        decision++;
        break;
    case 3:
        event = PLAYER_STOP_MOVING;
        decision++;
        break;
    default:
        decision=0;
    }

}
