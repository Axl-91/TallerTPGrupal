#ifndef __SHOOTING_RAYCASTER__
#define __SHOOTING_RAYCASTER__

#include <iostream>
#include "CollisionMap.h"
#include "../common_src/Vector.h"

#define PI 3.14159265358979323846

class ShootingRaycaster{
private:
    Vector rayV;
    Vector rayH;
    Vector rayFinal;
    Vector &posPlayer;
    float distV = 10000;
    float distH = 10000;
    float &angPlayer;
    float angRay;
    CollisionMap &mapRay;
    float distT;
    void raycasterVertical();
    void raycasterHorizontal();
    void calcularRayFinal();
public:
    ShootingRaycaster(Vector &pos, float &anguloPlayer, CollisionMap &map);
    void crearRay(float &anguloRay);
    float getDistancia();
    ~ShootingRaycaster();
};

#endif
