#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Walls.h"
#include "Objects.h"

#define WEAPON_OFFSET 74
#define HEAL_OFFSET 177
#define ENEMY_VALUE 100

Map::Map(std::vector<std::vector<int>> &lvl): map(lvl){
	rows=lvl.size();
	cols=lvl[0].size();
	load(lvl);
	insertEnemy(1, 11, 4, ENEMY_VALUE);
	// insertObject(13, 4, ENEMY_VALUE);

	// Vector posEnemy(224, 96);
	// enemy = {posEnemy, 100};
	
}

void Map::load(std::vector<std::vector<int>> lvl){
	std::vector<int> auxVec(lvl.size());

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			if(map[i][j]>=400)
				map[i][j]-=400;
			if(map[i][j]>=100&&map[i][j]<200){
				insertObject(j,i,25);
				map[i][j]=0;
			}
			if(map[i][j]>=200&&map[i][j]<300){
				insertObject(j,i,26);
				map[i][j]=0;
			}
			if(map[i][j]>=300&&map[i][j]<400){
				insertObject(j,i,24);
				map[i][j]=0;
			}
		}
	}
}

void Map::insertWeaponWithCoords(int x, int y, int obj){
	int j=x/largoBloque;
	int i=y/largoBloque;
	insertObject(j,i,obj-WEAPON_OFFSET);
}

void Map::insertEnemy(int ID, int x, int y, int obj){
	Vector posVect((x+1)*largoBloque-largoBloque/2,(y+1)*largoBloque-largoBloque/2);
	// Enemy_t auxObj = {posVect, 0, obj};
	Enemy_t auxObj;
	auxObj.pos=posVect;
	auxObj.ang=0;
	auxObj.type=obj;
	mapEnemies[ID]=auxObj;
}

std::map<int, Enemy_t>& Map::getEnemies(){
	return mapEnemies;
}

void Map::insertObject(int x, int y, int obj){
	Vector posVect((x+1)*largoBloque-largoBloque/2,(y+1)*largoBloque-largoBloque/2);
	Objeto auxObj = {posVect, obj};
	std::pair<int,int> posPair(posVect.posX, posVect.posY);
	mapObj[posPair]=auxObj;
}

void Map::eraseObj(float x, float y){
	int posX = x - (int)x%largoBloque+largoBloque/2;
	int posY = y - (int)y%largoBloque+largoBloque/2;
	mapObj.erase(std::pair<int,int>(posX, posY));

}

void Map::setRenderer(SDL_Renderer* renderer){
	walls.setRenderer(renderer);
	objects.setRenderer(renderer);
	enemies.setRenderer(renderer);
}

int Map::getLongBloques(){
	return largoBloque;
}

bool Map::hayCoordenadas(float &x, float &y){
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

bool Map::hayCoordenadas(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();	
	return hayCoordenadas(x, y);
}

int Map::getBloque(float &x, float &y){
	int posX = x/largoBloque;
	int posY = y/largoBloque;

	return map[posY][posX];
}

int Map::getBloque(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();
	return getBloque(x, y);
}

void Map::setWall(Vector &vector, bool dark){
	int tipoWall = getBloque(vector) - 1;
	walls.setWall(tipoWall);
	if (dark){
		walls.setDark();
	}
}

void Map::setColWall(float &pos){
	int y = 0;
	int largoCol = 1;
	int rayInt = floor(pos);
	int posWall = rayInt % largoBloque;
	walls.recortar(posWall, y, largoCol, largoBloque);
}

void Map::renderWall(int &posX, int &posY, int &largo, int &alto){
	walls.render(posX, posY, largo, alto);
}

void Map::addObject(Vector &posicion, int tipo){
	std::pair<int,int> auxPair(posicion.posX,posicion.posY);
	Objeto obj = {posicion, tipo};
	mapObj[auxPair]=obj;
}

void agregarVectDist(std::vector<Objeto> &v, Objeto &obj, Vector &pos){
	float dist = pos.distancia(obj.posicion);
	for (auto i = v.begin(); i != v.end(); ++i){
		Objeto objVec = *i;
		float distV = pos.distancia(objVec.posicion);
		if (dist > distV){
			v.insert(i, obj);
			return;
		}
	}
	v.push_back(obj);
}

std::vector<Objeto> Map::ordenarObjects(Vector &pos){
	std::vector<Objeto> vectorAux;
	int auxSprite;
	Objeto auxObj;
	for (auto obj : mapObj){
		agregarVectDist(vectorAux, obj.second, pos);
	}

	for (auto enemy : mapEnemies){
		enemies.defineSprite(enemy.second, pos, auxSprite);
		auxObj={enemy.second.pos, auxSprite};
		agregarVectDist(vectorAux, auxObj, pos);
	}
	return vectorAux;
}

void Map::setObj(int &tipo){
	if(tipo>=100)
		enemies.setEnemy(tipo);
	else
		objects.setObject(tipo);
}

void Map::setColObject(int &pos, int type ){
	if(type>=100){
		setColEnemy(pos);
	}else
		objects.recortar(pos, 0, 1, 64);
}


void Map::setColEnemy(int &pos){
	enemies.recortar(pos, 0, 1, 64);
}

void Map::renderEnemy(int &posX, int &posY, int &largo, int &alto){
	enemies.render(posX, posY, largo, alto);
}


void Map::renderObject(int &posX, int &posY, int &largo, int &alto, int type){
	if(type>=100)
		renderEnemy(posX, posY, largo, alto);
	else
		objects.render(posX, posY, largo, alto);
}

Map::~Map(){}
