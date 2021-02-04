#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>

class Vector{
private:
public:
    float posX;
    float posY;

	Vector(float x=0, float y=0);
    float getX();
    float getY();
        float getAngle(Vector v);
    float getAngle();

    Vector operator-(Vector &v);
    void setX(float &x);
    void setY(float &y);
    void set(float &x,float &y);
    void sumar (Vector vector);
    void restar (Vector vector);
    float distancia (Vector vector);
    friend std::ostream & operator<< (std::ostream &os, Vector &v);
	~Vector();
};

#endif
