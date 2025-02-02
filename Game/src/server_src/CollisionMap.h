#ifndef _COLLISION_MAP_H_
#define _COLLISION_MAP_H_

#include <vector>
#include "collisions/Quadtree.h"
#include "collisions/Collidable.h"
#include "../common_src/types.h"

//Clase que se ocupa de relacionar las colisiones con el comportamiento del jugador
class CollisionMap{
   	int largoBloque;
	int rows;
	int cols;
	std::vector<std::vector<int>> map;
	Quadtree collisionTree;

public:
    CollisionMap(std::vector<std::vector<int>> &lvl);
    ~CollisionMap();
	void erase(float x, float y);
	void erase(circle &pPos);

	void insert(float x, float y, int value);
	void detectCollision(circle &c, float dx, float dy, std::vector<Collidable*> &col);

	int getLongBloques();
	bool hayCoordenadas(float &x, float &y);
	bool hayCoordenadas(Vector &posicion);
	int getBloque(float &x, float &y);
	int getBloque(Vector &posicion);
};




#endif
