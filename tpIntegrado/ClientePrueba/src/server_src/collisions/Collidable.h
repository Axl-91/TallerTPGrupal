#ifndef _Collidable_H_
#define _Collidable_H_

#include <iostream>
#include "../serverPlayer.h"
#include "../../common_src/Circle.h"
#include "../../common_src/Vector.h"

#define MAP_AMMO 20

#define COLLIDABLE_OFFSET 100
#define COLLECTIBLE_OFFSET 10
#define KEY_OFFSET 100
#define HEAL_OFFSET 110
#define AMMO_OFFSET 120
#define WEAPON_OFFSET 130
#define TREASURE_OFFSET 140
#define IMMOVABLE_OBJECT_OFFSET 200
#define WALL_OFFSET 400

#define TREASURE_POINTS_CROSS 100
#define TREASURE_POINTS_CALIZ 100
#define TREASURE_POINTS_CHEST 100
#define TREASURE_POINTS_CROWN 100

#define HEAL_BLOOD 1
#define HEAL_FOOD 10
#define HEAL_MEDICAL_EQUIPMENT 20


class Collidable{
protected:
    float xInit;
    float xEnd;
    float yInit;
    float yEnd;
    
public:
    Collidable(){};
    Collidable(float xI, float yI, float xE, float yE);
    ~Collidable();

    bool isInside(circle &c);
    bool isInRectangle(float xI, float yI, float xE, float yE);
    virtual bool detectCollision(circle &c, float dX,float dY)=0;
    bool detectCollision(float x, float y, float dX,float dY);
    virtual int collide(ServerPlayer &p) = 0;
    Collidable& operator=(Collidable const &other); 
    friend std::ostream & operator<< (std::ostream &os, Collidable &c);

    Collidable* makeCollidable(int xI, int yI, int cellWidth, int opt);
};

#endif
