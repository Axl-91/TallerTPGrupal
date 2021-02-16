#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Walls.h"
//#include "Objects.h"

#define KEY_OFFSET_VALUE 101
#define WEAPON_OFFSET_VALUE 127
#define HEAL_OFFSET_VALUE 109
#define AMMO_OFFSET_VALUE 116
#define TREASURE_OFFSET_VALUE 132
#define IMMOVABLE_OBJECT_OFFSET_VALUE 188


#define ENEMY_OFFSET 100

Map::Map(std::vector<std::vector<int>> &lvl): map(lvl){
	rows=lvl.size();
	cols=lvl[0].size();
	load(lvl);
}

void Map::updateEnemy(Player_t &p){
	if(p.currentWP!=WP_SECONDARY)
		mapEnemies[p.ID].type = (enemy_type_t) p.currentWP;
	else
		mapEnemies[p.ID].type = (enemy_type_t) p.secondaryWP;

	if(p.lifes == 0)
		mapEnemies[p.ID].dead = true;
		
	mapEnemies[p.ID].playerInfo = p;
	enemies.defineFrame(mapEnemies[p.ID]);
}

void Map::load(std::vector<std::vector<int>> lvl){
	std::vector<int> auxVec(lvl.size());

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			if(map[i][j]>=400)
				map[i][j]-=400;

			if(map[i][j]>=MOVABLE_DOOR_OFFSET&&map[i][j]<MOVABLE_DOOR_OFFSET+COLLIDABLE_OFFSET){
				map[i][j]-=300;
			}


			if(map[i][j]>=IMMOVABLE_OBJECT_OFFSET&&map[i][j]<IMMOVABLE_OBJECT_OFFSET+COLLIDABLE_OFFSET){
				insertObject(j,i,map[i][j]-IMMOVABLE_OBJECT_OFFSET_VALUE);
				map[i][j]=0;
			}
			if(map[i][j]>=KEY_OFFSET&&map[i][j]<KEY_OFFSET+COLLECTIBLE_OFFSET){
				insertObject(j,i,map[i][j]-KEY_OFFSET_VALUE);
				map[i][j]=0;
			}
			if(map[i][j]>=HEAL_OFFSET&&map[i][j]<HEAL_OFFSET+COLLECTIBLE_OFFSET){
				insertObject(j,i,map[i][j]-HEAL_OFFSET_VALUE);
				map[i][j]=0;
			}
			if(map[i][j]>=AMMO_OFFSET&&map[i][j]<AMMO_OFFSET+COLLECTIBLE_OFFSET){
				insertObject(j,i,map[i][j]-AMMO_OFFSET_VALUE);
				map[i][j]=0;
			}
			if(map[i][j]>=WEAPON_OFFSET&&map[i][j]<WEAPON_OFFSET+COLLECTIBLE_OFFSET){
				insertObject(j,i,map[i][j]-WEAPON_OFFSET_VALUE);
				map[i][j]=0;
			}
			if(map[i][j]>=TREASURE_OFFSET&&map[i][j]<TREASURE_OFFSET+COLLECTIBLE_OFFSET){
				insertObject(j,i,map[i][j]-TREASURE_OFFSET_VALUE);
				map[i][j]=0;
			}

		}
	}
}

void Map::insertWeaponWithCoords(int x, int y, int obj){
	int j=x/longTile;
	int i=y/longTile;
	insertObject(j,i,obj-WEAPON_OFFSET_VALUE);
}

void Map::insertEnemy(Player_t &p){
	Enemy_t e;
	e.playerInfo = p;
	e.dead = false;
	e.moving_frame = 0;
	e.shooting_frame = 0;
	e.dead_frame = 0;
	e.type=(enemy_type_t) p.currentWP;
	mapEnemies[p.ID] = e;
}

std::map<int, Enemy_t>& Map::getEnemies(){
	return mapEnemies;
}

void Map::insertObject(int x, int y, int obj){
	Vector posVect((x+1)*longTile-longTile/2,(y+1)*longTile-longTile/2);
	Object_t auxObj = {posVect, obj};
	std::pair<int,int> posPair(posVect.posX, posVect.posY);
	mapObj[posPair]=auxObj;
}


void Map::setRenderer(SDL_Renderer* renderer){
	walls.setRenderer(renderer);
	std::cout << "map: setrenderer "<< std::endl;

	objects.setRenderer(renderer);
	std::cout << "map: objeto rederizado "<< std::endl;

	enemies.setRenderer(renderer);
}

int Map::getLongTiles(){
	return longTile;
}

bool Map::validPosition(float &x, float &y){
	int posX = x/longTile;
	int posY = y/longTile;

	if (posX >= cols || posX < 0){
		return false;
	}
	if (posY >= rows || posY < 0){
		return false;
	}
	
	return true;
}

bool Map::validPosition(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();	
	return validPosition(x, y);
}

int Map::getTile(float &x, float &y){
	int posX = x/longTile;
	int posY = y/longTile;
	return map[posY][posX];
}

int Map::getTile(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();
	return getTile(x, y);
}

void Map::setWall(Vector &vector, bool dark){
	int tipoWall = getTile(vector) - 1;
	walls.setWall(tipoWall);
	if (dark){
		walls.setDark();
	}
}

void Map::setColWall(float &pos){
	int y = 0;
	int lenghtCol = 1;
	int rayInt = floor(pos);
	int posWall = rayInt % longTile;
	walls.cutFromTexture(posWall, y, lenghtCol, longTile);
}

void Map::renderWall(int &posX, int &posY, int &lenght, int &height){
	walls.render(posX, posY, lenght, height);
}

void Map::addObject(Vector &pos, int tipo){
	std::pair<int,int> auxPair(pos.posX,pos.posY);
	Object_t obj = {pos, tipo};
	mapObj[auxPair]=obj;
}

void addVectDist(std::vector<Object_t> &v, Object_t &obj, Vector &pos){
	float dist = pos.getDistance(obj.position);
	for (auto i = v.begin(); i != v.end(); ++i){
		Object_t objVec = *i;
		float distV = pos.getDistance(objVec.position);
		if (dist > distV){
			v.insert(i, obj);
			return;
		}
	}
	v.push_back(obj);
}

std::vector<Object_t> Map::orderObjects(Vector &pos){
	std::vector<Object_t> vectorAux;
	int auxSprite;
	Object_t auxObj;
	for (auto obj : mapObj){
		addVectDist(vectorAux, obj.second, pos);
	}
	for (auto enemy : mapEnemies){
		enemies.defineSprite(enemy.second, pos, auxSprite);
		Vector auxPos(enemy.second.playerInfo.x, enemy.second.playerInfo.y);
		auxObj={auxPos, auxSprite};
		addVectDist(vectorAux, auxObj, pos);
	}
	return vectorAux;
}

void Map::setObj(int &type){
	if(type>=ENEMY_OFFSET)
		enemies.setEnemyRenderSprite(type);
	else
		objects.setObject(type);
}

void Map::setColObject(int &pos, int type){
	if(type>=ENEMY_OFFSET){
		setColEnemy(pos);
	}else
		objects.cutFromTexture(pos, 0, 1, 64);
}

void Map::setColEnemy(int &pos){
	enemies.cutFromTexture(pos, 0, 1, 64);
}

void Map::renderEnemy(int &posX, int &posY, int &lenght, int &height){
	enemies.render(posX, posY, lenght, height);
}


void Map::renderObject(int &posX, int &posY, int &lenght, int &height, int type){
	if(type>=ENEMY_OFFSET){
		renderEnemy(posX, posY, lenght, height);
	}
	else{
		objects.render(posX, posY, lenght, height);
	}
}

Map::~Map(){}

void Map::update(Map_change_t &aMapChange){

	// if(aMapChange.value > 300){
	// 	openDoor(aMapChange.x,aMapChange.y, aMapChange.value);
	// }

	eraseObj(aMapChange.x, aMapChange.y);
	if(aMapChange.value != 0&& aMapChange.value <300){
		insertWeaponWithCoords(aMapChange.x,aMapChange.y, aMapChange.value);
	}
}

void Map::eraseObj(float x, float y){
	int posX = x - (int)x%longTile+longTile/2;
	int posY = y - (int)y%longTile+longTile/2;
	mapObj.erase(std::pair<int,int>(posX, posY));

}
