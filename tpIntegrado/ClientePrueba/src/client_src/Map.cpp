#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Walls.h"
//#include "Objects.h"

#define KEY_OFFSET 101
#define WEAPON_OFFSET 127
#define HEAL_OFFSET 109
#define AMMO_OFFSET 116
#define TREASURE_OFFSET 132
#define INMOVABLE_OBJECT_OFFSET 188


#define ENEMY_VALUE 100

Map::Map(std::vector<std::vector<int>> &lvl): map(lvl){
	rows=lvl.size();
	cols=lvl[0].size();
	load(lvl);
}

void Map::updateEnemy(Player_t &p){
	insertEnemy(p);
}

void Map::load(std::vector<std::vector<int>> lvl){
	std::vector<int> auxVec(lvl.size());

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			if(map[i][j]>=400)
				map[i][j]-=400;
			if(map[i][j]>=200&&map[i][j]<300){
				insertObject(j,i,map[i][j]-INMOVABLE_OBJECT_OFFSET);
				map[i][j]=0;
			}
			if(map[i][j]>=100&&map[i][j]<110){
				insertObject(j,i,map[i][j]-KEY_OFFSET);
				map[i][j]=0;
			}
			if(map[i][j]>=110&&map[i][j]<120){
				insertObject(j,i,map[i][j]-HEAL_OFFSET);
				map[i][j]=0;
			}
			if(map[i][j]>=120&&map[i][j]<130){
				insertObject(j,i,map[i][j]-AMMO_OFFSET);
				map[i][j]=0;
			}
			if(map[i][j]>=130&&map[i][j]<140){
				insertObject(j,i,map[i][j]-WEAPON_OFFSET);
				map[i][j]=0;
			}
			if(map[i][j]>=140&&map[i][j]<150){
				insertObject(j,i,map[i][j]-TREASURE_OFFSET);
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
void Map::insertEnemy(Player_t &p){
	mapEnemies[p.ID] = p;
}

std::map<int, Player_t>& Map::getEnemies(){
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
	std::cout << "map: setrenderer "<< std::endl;

	objects.setRenderer(renderer);
	std::cout << "map: objeto rederizado "<< std::endl;

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
		Vector auxPos(enemy.second.x, enemy.second.y);
		auxObj={auxPos, auxSprite};
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
	if(type>=100){
		renderEnemy(posX, posY, largo, alto);
	}
	else{
		objects.render(posX, posY, largo, alto);
	}
}

Map::~Map(){}

void Map::update(Map_change_t &aMapChange){
	eraseObj(aMapChange.x, aMapChange.y) ;
	if(aMapChange.value != 0){
		insertWeaponWithCoords(aMapChange.x,aMapChange.y, aMapChange.value);
	}
}