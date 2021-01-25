#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>

class Vector{
private:
public:
    float posX;
    float posY;

    // Vector();
	Vector(float x=0, float y=0);
    float getX();
    float getY();
    void setX(float &x);
    void setY(float &y);
    void set(float &x,float &y);

    void sumar (Vector vector);
    void restar (Vector vector);
    float distancia (Vector vector);
    // Vector& operator=(Vector &other);
    friend std::ostream & operator<< (std::ostream &os, Vector &v);
	~Vector();
};

#endif
