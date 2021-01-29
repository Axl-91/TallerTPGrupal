#ifndef _COLLISION_MAP_H_
#define _COLLISION_MAP_H_

#include <vector>
#include "collisions/Quadtree.h"
#include "collisions/Collidable.h"

#include "../common_src/Circle.h"

class CollisionMap{
   	int largoBloque;
	int rows;
	int cols;
    //El mapa deberia ser de dimensiones variables
	// int map[MAP_ROWS][MAP_COLS];
	Quadtree collisionTree;

public:
    CollisionMap(std::vector<std::vector<int>> &lvl);
    ~CollisionMap();
	void erase(float x, float y);
	void erase(circle &pPos);

	void insert(float x, float y, int value);
	void detectCollision(circle &c, float dx, float dy, std::vector<Collidable*> &col);

};




#endif
