#include "ServerMissile.h"
#include <cmath>

#define DISTANCE_DAMAGE 128

ServerMissile::ServerMissile(size_t anID, float x, float y, 
                            float a, float dX, float dY, int d){
    ID = anID;
    step = MISSILE_STEP;
    pos = {x, y, MISSILE_RADIUS};
    angle = a;
    damage = d;
  	dirX = step * cos(angle);
	dirY = step * sin(angle); 

}
ServerMissile::~ServerMissile(){}

void ServerMissile::getInfo(Missile_t &m){
    m.ID = ID;
    m.x = pos.x;
    m.y = pos.y;
    m.dirX = dirX;
    m.dirY = dirY;
    m.damage = damage;
    m.ang = angle;
    m.exploding = exploded;
}

void ServerMissile::move(){
    pos.x += dirX;
    pos.y += dirY;
}

int ServerMissile::getExplosionDamage(float playerPosX, float playerPosY){
    Vector playerPos(playerPosX, playerPosY);
    Vector mPos(pos.x, pos.y);
    float auxDamage = damage;
    float distance = mPos.getDistance(playerPos);
    float coef = (DISTANCE_DAMAGE-distance)/DISTANCE_DAMAGE;
    if(coef<0)
        coef = 0;

    return (int) auxDamage*coef;
}


bool ServerMissile::detectCollision(ServerPlayer &player){
    circle cPlayerPos;
    player.getPosition(cPlayerPos);
    float minDistance = cPlayerPos.radius + pos.radius;
    Vector playerPos(cPlayerPos.x, cPlayerPos.y);
    Vector mPos(pos.x, pos.y);
    float distance = playerPos.getDistance(mPos);
    return distance <= minDistance? true :false;
}

void ServerMissile::getPosition(circle &p){
    p = pos;
}


void ServerMissile::getDirection(float &dx, float &dy){
    dx = dirX;
    dy = dirY;
}


bool ServerMissile::hasExploded(){
    return exploded;
}


void ServerMissile::explode(){
    exploded = true;
}
