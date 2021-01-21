#ifndef _Collidable_H_
#define _Collidable_H_

#include <iostream>
#include "../Player.h"
#include "../Circle.h"
#include "../Vector.h"

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
    virtual int collide(Player &p)=0;
    Collidable& operator=(Collidable const &other); 
    friend std::ostream & operator<< (std::ostream &os, Collidable &c);


    Collidable* makeCollidable(int xI, int yI, int cellWidth, int opt);
};

#endif
