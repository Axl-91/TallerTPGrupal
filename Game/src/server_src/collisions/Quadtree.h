#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <vector>
#include <queue>
#include "QuadNode.h"
#include "../../common_src/types.h"



//arbol de deteccion de colisiones
class Quadtree{
    QuadNode root;
public:
    Quadtree(int rows, int cols, std::vector<std::vector<int>> &map, int cellWidth);
    Quadtree(){}
    ~Quadtree();
    void query();
    void print(std::ostream &os);
    void detectCollision(circle &c, float dX, float dY, std::vector<Collidable*> &col);
    void insert(float x, float y, int cellWidth, int value);
    void erase(float x, float y);
    void erase(circle pPos);
};



#endif
