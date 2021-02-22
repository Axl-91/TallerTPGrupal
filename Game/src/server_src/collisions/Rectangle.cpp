#include <iostream>
#include "Collidable.h"
#include "Rectangle.h"

Rectangle::Rectangle(){}
Rectangle::Rectangle(int x_, int y_, int w_, int h_){
    xInit=x_;
    yInit=y_;
    xEnd=w_;
    yEnd=h_;
}
Rectangle::~Rectangle(){}

bool Rectangle::contains(Collidable &c) {
    bool b=c.isInRectangle(xInit, yInit, xEnd, yEnd);

    return b;
}


bool Rectangle::contains(circle &c) {
    Rectangle aux(xInit-c.radius,yInit-c.radius, xEnd+c.radius, yEnd+c.radius);

    return aux.contains(c.x, c.y);
}

bool Rectangle::contains(float x, float y) {
    bool contX = xInit<=x && xEnd>=x;
    bool contY = yInit<=y && yEnd>=y;

    return contX && contY;
}

std::ostream & operator<< (std::ostream &os, Rectangle &r){
    os<<"xInit: "<<r.xInit<<std::endl;
    os<<"xEnd: "<<r.xEnd<<std::endl;

    os<<"yInit: "<<r.yInit<<std::endl;
    os<<"yEnd: "<<r.yEnd<<std::endl;

    return os;

}
