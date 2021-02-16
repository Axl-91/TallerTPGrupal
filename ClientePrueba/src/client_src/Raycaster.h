#ifndef __RAYCASTER__
#define __RAYCASTER__

#include <iostream>
#include "Map.h"
#include "../common_src/Vector.h"

class Raycaster{
private:
    Vector rayV;
    Vector rayH;
    Vector rayFinal;
    Vector &posPlayer;
    float distV = 10000;
    float distH = 10000;
    float &angPlayer;
    float angRay;
    Map &mapRay;
    float distT;
    void raycasterVertical();
    void raycasterHorizontal();
    void finalRay();
public:
    Raycaster(Vector &pos, float &angPlayer, Map &map);
    void makeRay(float &angleRay);
    float getDistance();
    void render(int &pos);
    ~Raycaster();
};

#endif
