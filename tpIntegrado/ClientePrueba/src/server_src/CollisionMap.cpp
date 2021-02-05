#include "CollisionMap.h"

CollisionMap::CollisionMap(std::vector<std::vector<int>> &lvl):
largoBloque(64),
map(lvl),
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




int CollisionMap::getLongBloques(){
	return largoBloque;
}

bool CollisionMap::hayCoordenadas(float &x, float &y){
	int posX = x/largoBloque;
	int posY = y/largoBloque;

	if (posX >= cols || posX < 0){
		return false;
	}
	if (posY >= rows || posY < 0){
		return false;
	}
	
	return true;
}

bool CollisionMap::hayCoordenadas(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();	
	return hayCoordenadas(x, y);
}

int CollisionMap::getBloque(float &x, float &y){
	int posX = x/largoBloque;
	int posY = y/largoBloque;
	return map[posY][posX];
}

int CollisionMap::getBloque(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();
	return getBloque(x, y);
}
