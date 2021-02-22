#include <iostream>
#include "MovableFalseWall.h"
#include "Rectangle.h"
#include <iostream>

MovableFalseWall::MovableFalseWall(int xI, int yI, int cellWidth, int doorType)
{
    xInit=xI*cellWidth;
    xEnd=xI*cellWidth+cellWidth;
    yInit=yI*cellWidth; 
    yEnd=yI*cellWidth+cellWidth;
}

MovableFalseWall::~MovableFalseWall(){}


int MovableFalseWall::collide(ServerPlayer &p){
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

    if(p.isOpeningDoor()==true){
            return 301;
    }

    p.setDirection(dX, dY);

    return 300;
}

bool MovableFalseWall::detectCollision(circle &c, float dX,float dY){

    Rectangle aux(xInit-c.radius,yInit-c.radius, xEnd+c.radius, yEnd+c.radius);
    return aux.contains(c.x+dX, c.y+dY);
}
