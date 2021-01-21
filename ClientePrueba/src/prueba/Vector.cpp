#include "Vector.h"
#include <math.h>
#include <iostream>
Vector::Vector(float x, float y): posX(x), posY(y) {}

float Vector::getX(){
    return posX;
}

float Vector::getY(){
    return posY;
}

void Vector::sumar(Vector vector){
    posX += vector.getX();
    posY += vector.getY();
}

void Vector::restar(Vector vector){
    posX -= vector.getX();
    posY -= vector.getY();
}

float Vector::distancia(Vector vector){
    float x = vector.getX() - posX;
    float y = vector.getY() - posY;
    return (sqrt((x*x) + (y*y)));
}

std::ostream & operator<< (std::ostream &os, Vector &v){
    os<<"x: "<<v.posX<<std::endl;
    os<<"y: "<<v.posY<<std::endl;
    return os;
}


Vector::~Vector(){}
