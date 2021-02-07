#include <iostream>
#include "Collidable.h"
#include "ImmovableWall.h"
#include "ImmovableObject.h"
#include "CollectWeapon.h"
#include "CollectHeal.h"
#include "CollectAmmo.h"
#include "CollectKey.h"
#include "CollectTreasure.h"

#include "../../common_src/Vector.h"
#include "Rectangle.h"

Collidable::Collidable(float xI, float yI, float xE, float yE):
xInit(xI), xEnd(xE), yInit(yI), yEnd(yE){}

Collidable::~Collidable(){}

Collidable* Collidable::makeCollidable(int xI, int yI, int cellWidth, int opt){
    if(opt>WEAPON_OFFSET && opt<WEAPON_OFFSET + COLLECTIBLE_OFFSET){
        return new CollectWeapon(xI, yI, cellWidth, opt-WEAPON_OFFSET);
    }else if(opt>TREASURE_OFFSET && opt<TREASURE_OFFSET + COLLECTIBLE_OFFSET){
        return new CollectTreasure(xI, yI, cellWidth, opt-TREASURE_OFFSET);
    }else if(opt>KEY_OFFSET && opt<KEY_OFFSET + COLLECTIBLE_OFFSET){
        return new CollectKey(xI, yI, cellWidth, opt-KEY_OFFSET);
    }else if(opt>HEAL_OFFSET && opt<HEAL_OFFSET + COLLECTIBLE_OFFSET){
        return new CollectHeal(xI, yI, cellWidth, opt-HEAL_OFFSET);
    }else if(opt>AMMO_OFFSET && opt<AMMO_OFFSET + COLLECTIBLE_OFFSET){
        return new CollectAmmo(xI, yI, cellWidth, opt-AMMO_OFFSET);
    }else if(opt>IMMOVABLE_OBJECT_OFFSET && opt<IMMOVABLE_OBJECT_OFFSET + COLLIDABLE_OFFSET){
        return new ImmovableObject(xI, yI, cellWidth, opt-IMMOVABLE_OBJECT_OFFSET);
    }else if(opt>WALL_OFFSET && opt<WALL_OFFSET + COLLIDABLE_OFFSET){
        return new ImmovableWall(xI, yI, cellWidth, opt-WALL_OFFSET);
    }else {
        //TIRAR ERROR!!!
        return new ImmovableWall(xI, yI, cellWidth, opt-WALL_OFFSET);
    }
}

bool Collidable::isInside(circle &c){
    Vector init(xInit,yInit);
    Vector end(xEnd,yEnd);
    Vector cCenter(c.x, c.y);
    if(cCenter.distancia(init)<c.radius&&cCenter.distancia(end)<c.radius)
        return true;
    return false;
}


bool Collidable::isInRectangle(float xI, float yI, float xE, float yE){
    bool isInX = xInit>=xI && xEnd<=xE;
    bool isInY = yInit>=yI && yEnd<=yE;

    return isInX && isInY;
}

Collidable& Collidable::operator=(Collidable const &other){
    xInit=other.xInit;
    xEnd=other.xEnd;
    yInit=other.yInit;
    yEnd=other.yEnd;

    return *this;
}


bool Collidable::detectCollision(float x, float y, float dX,float dY){
    bool collX = xInit<=x+dX && xEnd>=x+dX;
    bool collY = yInit<=y+dY && yEnd>=y+dY;
    bool coll = collX && collY;

    return coll;
}



std::ostream & operator<< (std::ostream &os, Collidable &c){
    os<<"xInit: "<<c.xInit<<std::endl;
    os<<"xEnd: "<<c.xEnd<<std::endl;

    os<<"yInit: "<<c.yInit<<std::endl;
    os<<"yEnd: "<<c.yEnd<<std::endl;

    return os;
}

