#include "svMap.h"

#define IMMOVABLE_OBJECT_OFFSET_VALUE 188


#define ENEMY_VALUE 100

svMap::svMap(std::vector<std::vector<int>> &lvl): map(lvl){
	rows=lvl.size();
	cols=lvl[0].size();
	load(lvl);
}

void svMap::load(std::vector<std::vector<int>> lvl){
	std::vector<int> auxVec(lvl.size());

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			if(map[i][j]>=400)
				map[i][j]-=400;
			if(map[i][j]>=IMMOVABLE_OBJECT_OFFSET&&map[i][j]<IMMOVABLE_OBJECT_OFFSET+COLLIDABLE_OFFSET){
				insertObject(j,i,map[i][j]-IMMOVABLE_OBJECT_OFFSET_VALUE);
				map[i][j]=0;
			}
		}
	}
}

void svMap::insertObject(int x, int y, int obj){
	Vector posVect((x+1)*longTile-longTile/2,(y+1)*longTile-longTile/2);
	Object_t auxObj = {posVect, obj};
	std::pair<int,int> posPair(posVect.posX, posVect.posY);
	mapObj[posPair]=auxObj;
}

int svMap::getLongTiles(){
	return longTile;
}

bool svMap::validPosition(float &x, float &y){
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

bool svMap::validPosition(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();	
	return validPosition(x, y);
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

// std::vector<Object_t> svMap::orderObjects(Vector &pos){
// 	std::vector<Object_t> vectorAux;
// 	int auxSprite;
// 	Object_t auxObj;
// 	for (auto obj : mapObj){
// 		addVectDist(vectorAux, obj.second, pos);
// 	}
// 	for (auto enemy : mapEnemies){
// 		enemies.defineSprite(enemy.second, pos, auxSprite);
// 		Vector auxPos(enemy.second.playerInfo.x, enemy.second.playerInfo.y);
// 		auxObj={auxPos, auxSprite};
// 		addVectDist(vectorAux, auxObj, pos);
// 	}
// 	return vectorAux;
// }

int svMap::getTile(float &x, float &y){
	int posX = x/longTile;
	int posY = y/longTile;
	return map[posY][posX];
}

int svMap::getTile(Vector &vector){
	float x = vector.getX();
	float y = vector.getY();
	return getTile(x, y);
}


svMap::~svMap(){}
