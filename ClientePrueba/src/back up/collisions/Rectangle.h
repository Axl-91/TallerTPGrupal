#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "Collidable.h"
#include "../Circle.h"

class Rectangle{
//    float xInit, yInit, xEnd, yEnd; // coordenadas x,y en el plano / ancho y alto del plano

public:
    float xInit, yInit, xEnd, yEnd; // coordenadas x,y en el plano / ancho y alto del plano

    Rectangle();
    Rectangle(int x_, int y_, int w_, int h_);
    ~Rectangle();

    bool contains(Collidable &c);
    bool contains(float x, float y);
    bool contains(circle &c);

    friend std::ostream & operator<< (std::ostream &os, Rectangle &r);

};



#endif
