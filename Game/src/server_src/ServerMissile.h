#ifndef _SERVER_MISSILE_H_
#define _SERVER_MISSILE_H_

#include "../common_src/types.h"
#include "serverPlayer.h"
#define MISSILE_STEP 5 
#define MISSILE_RADIUS 5 

class ServerMissile{
    size_t ID;
    int step;
    circle pos;
    float angle;
    float dirX;
    float dirY;
    int damage;
    bool exploded;
public:
    ServerMissile(size_t ID, float x, 
                float y, float a, 
                float dX, float dY, 
                int damage);
    ~ServerMissile();
    void getInfo(Missile_t &m);
	void getPosition(circle &p);
	void getDirection(float &dx,float &dy);
	int getExplosionDamage(float playerPosX, float playerPosY);

    void move();
    void explode();
    bool hasExploded();
    bool detectCollision(ServerPlayer &player);

};





#endif
