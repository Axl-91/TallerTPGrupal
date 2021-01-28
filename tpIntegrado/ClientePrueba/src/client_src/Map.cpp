#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Walls.h"
// #include "Objects.h"


#define WEAPON_OFFSET 74
#define HEAL_OFFSET 177

Map::Map(std::vector<std::vector<int>> &lvl): map(lvl){
	rows=lvl.size();
	cols=lvl[0].size();
	load(lvl);
}


void Map::load(std::vector<std::vector<int>> lvl){
	std::vector<int> auxVec(lvl.size());

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			if(map[i][j]>=400)
				map[i][j]-=400;
			if(map[i][j]>=100&&map[i][j]<200){
				insertObject(j,i,map[i][j]-WEAPON_OFFSET);
				map[i][j]=0;
			}
			if(map[i][j]>=200&&map[i][j]<300){
				insertObject(j,i,map[i][j]-HEAL_OFFSET);
				map[i][j]=0;
			}
			if(map[i][j]>=300&&map[i][j]<400){
				insertObject(j,i,28);
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

// int Map::getCantObjects(){
// 	return vectObj.size();
// }

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
	for (auto obj : mapObj){
		agregarVectDist(vectorAux, obj.second, pos);
	}
	return vectorAux;
}
// void Map::ordenarObjects(Vector &pos){
// 	std::vector<Objeto> vectorAux;

// 	for (Objeto obj : vectObj){
// 		agregarVectDist(vectorAux, obj, pos);
// 	}
// 	vectObj.swap(vectorAux);
// }

// Vector Map::getPosObj(int &pos){
// 	Objeto objPedido = vectObj.at(pos);
// 	return objPedido.posicion;
// }

// int Map::getTipoObj(int &pos){
// 	Objeto objPedido = vectObj.at(pos);
// 	return objPedido.tipoObjecto;	
// }

void Map::setObj(int &tipo){
	objects.setObject(tipo);
}

void Map::setColObject(int &pos){
	objects.recortar(pos, 0, 1, 64);
}

void Map::renderObject(int &posX, int &posY, int &largo, int &alto){
	objects.render(posX, posY, largo, alto);
}

Map::~Map(){}

void Map::update(Map_change_t &aMapChange){
	// map[aMapChange.x][aMapChange.y] = aMapChange.value;
	aMapChange.changeAvailable = false;
	// std::cout << "Map::update(): aMapchange.x: "<< aMapChange.x << "amapchange.y: " << aMapChange.y << std::endl;
	eraseObj(aMapChange.x, aMapChange.y) ;

	// eraseObj(aMapChange.x * 64 + 32, aMapChange.y * 64 + 32) ;
	if(aMapChange.value != 0){
		insertWeaponWithCoords(aMapChange.x,aMapChange.y, aMapChange.value);
		// Objeto aux = {Vector((aMapChange.x+1)*64-32,(aMapChange.y+1)*64-32), aMapChange.value-WEAPON_OFFSET};
		// vectObj.emplace_back(aux);
	}
}