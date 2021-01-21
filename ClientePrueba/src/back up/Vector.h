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
    void sumar (Vector vector);
    void restar (Vector vector);
    float distancia (Vector vector);
    friend std::ostream & operator<< (std::ostream &os, Vector &v);
	~Vector();
};

#endif
