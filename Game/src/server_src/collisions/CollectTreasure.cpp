#include "CollectTreasure.h"


CollectTreasure::CollectTreasure(int xI, int yI, int cellWidth, int t):
Collectible(xI, yI, cellWidth){
    type=(treasure_t) t;


    if(type==CROSS)
        points=TREASURE_POINTS_CROSS;
    if(type==CALIZ)
        points=TREASURE_POINTS_CALIZ;
    if(type==CHEST)
        points=TREASURE_POINTS_CHEST;
    if(type==CROWN)
        points=TREASURE_POINTS_CROWN;

}

int CollectTreasure::collide(ServerPlayer &p){
    std::cout<<"colision cura"<<std::endl;

    return (int)p.addPoints(points)+TREASURE_OFFSET;
}

CollectTreasure::~CollectTreasure(){}
