#ifndef __RAYCASTER__
#define __RAYCASTER__

#include <iostream>
#include <cmath>
#include "svMap.h"
#include "../common_src/Vector.h"

class svRaycaster{
private:
    Vector rayV;
    Vector rayH;
    Vector rayFinal;
    Vector &posPlayer;
    float distV = 10000;
    float distH = 10000;
    float &angPlayer;
    float angRay;
    svMap &mapRay;
    float distT;
    void raycasterVertical();
    void raycasterHorizontal();
    void finalRay();
public:
    svRaycaster(Vector &pos, float &angPlayer, svMap &map);
    void makeRay(float &angleRay);
    float getDistance();
    ~svRaycaster();
};

#endif
