#include <iostream>
#include "ImmovableWall.h"
#include "Rectangle.h"

ImmovableWall::ImmovableWall(int xI, int yI, int cellWidth, int wall)
{
    xInit=xI*cellWidth;
    xEnd=xI*cellWidth+cellWidth;
    yInit=yI*cellWidth; 
    yEnd=yI*cellWidth+cellWidth;
}

ImmovableWall::~ImmovableWall(){}


int ImmovableWall::collide(ServerPlayer &p){
    float x;
    float y;
    float dX;
    float dY;

    p.getPosition(x,y);
    p.getDirection(dX,dY);
    if((xInit<x+16 && xEnd>x+16)==false && (xInit<x-16 && xEnd>x-16)==false)
        dX=0;
    if((yInit<y+16 && yEnd>y+16)==false && (yInit<y-16 && yEnd>y-16)==false)
        dY=0;

    p.setDirection(dX, dY);

    return 400;
}

bool ImmovableWall::detectCollision(circle &c, float dX,float dY){
    // std::cout<<"Collidable::detectCollision"<<std::endl;
    // std::cout<<"c.x: "<<c.x<<std::endl;
    // std::cout<<"c.y: "<<c.y<<std::endl;
    // std::cout<<*this<<std::endl;

    Rectangle aux(xInit-c.radius,yInit-c.radius, xEnd+c.radius, yEnd+c.radius);
    return aux.contains(c.x+dX, c.y+dY);
}
