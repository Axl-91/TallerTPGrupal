#include "CollisionMap.h"

CollisionMap::CollisionMap(std::vector<std::vector<int>> &lvl):
largoBloque(64),
collisionTree(lvl.size(),lvl[0].size(),lvl,largoBloque){
	rows=lvl.size();
	cols=lvl[0].size();
}
CollisionMap::~CollisionMap(){}

void CollisionMap::detectCollision(circle &c, float dx, float dy, std::vector<Collidable*> &col){
	collisionTree.detectCollision(c, dx,dy, col);
}


void CollisionMap::erase(float x, float y){
	collisionTree.erase(x, y);
}

void CollisionMap::erase(circle &pPos){
	collisionTree.erase(pPos);
}

void CollisionMap::insert(float x, float y, int value){
	int xAux=x/largoBloque;
	int yAux=y/largoBloque;
	collisionTree.insert(xAux, yAux, largoBloque, value);
}