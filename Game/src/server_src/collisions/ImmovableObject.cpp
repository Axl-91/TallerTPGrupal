#include <iostream>
#include "ImmovableObject.h"
#include "Rectangle.h"

ImmovableObject::ImmovableObject(int xI, int yI, int cellWidth, int wall)
{
    xInit=xI*cellWidth+cellWidth/4;
    xEnd=xI*cellWidth+cellWidth-cellWidth/4;
    yInit=yI*cellWidth+cellWidth/4; 
    yEnd=yI*cellWidth+cellWidth-cellWidth/4;
}

ImmovableObject::~ImmovableObject(){}


int ImmovableObject::collide(ServerPlayer &p){
    float x;
    float y;
    float dX;
    float dY;

    p.getPosition(x,y);
    p.getDirection(dX,dY);

    if((xInit<x+p.getRadius() && xEnd>x+p.getRadius())==false 
    && (xInit<x-p.getRadius() && xEnd>x-p.getRadius())==false)
        dX=0;
    if((yInit<y+p.getRadius() && yEnd>y+p.getRadius())==false && 
    (yInit<y-p.getRadius() && yEnd>y-p.getRadius())==false)
        dY=0;

    p.setDirection(dX, dY);

    return IMMOVABLE_OBJECT_OFFSET;
}

bool ImmovableObject::detectCollision(circle &c, float dX,float dY){
    Rectangle aux(xInit-c.radius,yInit-c.radius, xEnd+c.radius, yEnd+c.radius);
    return aux.contains(c.x+dX, c.y+dY);
}
