#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Map.h"
#include "Walls.h"
#include "Objects.h"


#define WEAPON_OFFSET 74
#define HEAL_OFFSET 177


Map::Map(std::vector<std::vector<int>> &lvl): map(lvl){
	rows=lvl.size();
	cols=lvl[0].size();
	load(lvl);
}

void Map::load(std::vector<std::vector<int>> lvl){
	std::vector<int> auxVec(lvl.size());
	// map=lvl;

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < cols; ++j){
			if(map[i][j]>=400)
				map[i][j]-=400;
			if(map[i][j]>=100&&map[i][j]<200){
				Objeto aux = {Vector((j+1)*64-32,(i+1)*64-32), map[i][j]-WEAPON_OFFSET};
				vectObj.emplace_back(aux);
				map[i][j]=0;
			}
			if(map[i][j]>=200&&map[i][j]<300){
				Objeto aux = {Vector((j+1)*64-32,(i+1)*64-32), map[i][j]-HEAL_OFFSET};
				vectObj.emplace_back(aux);
				map[i][j]=0;
			}
			if(map[i][j]>=300&&map[i][j]<400){
				Objeto aux = {Vector((j+1)*64-32,(i+1)*64-32), 28};
				vectObj.emplace_back(aux);
				map[i][j]=0;
			}
		}
	}
}


void Map::insertWeapon(int x, int y, int obj){
	int j=x/64;
	int i=y/64;
	Objeto aux = {Vector((j+1)*64-32,(i+1)*64-32), obj-WEAPON_OFFSET};
	vectObj.emplace_back(aux);
}



void Map::eraseObj(float x, float y){
	int xLimitInit = x - (int)x%largoBloque;
	int xLimitEnd = xLimitInit+largoBloque;

	int yLimitInit = y - (int)y%largoBloque;
	int yLimitEnd = yLimitInit+largoBloque;

	int xObj;
	int yObj;
	for(size_t i=0; i<vectObj.size(); i++)
	{
		xObj = vectObj[i].posicion.posX;
		yObj = vectObj[i].posicion.posY;
		if(xObj > xLimitInit && xObj < xLimitEnd &&
			yObj > yLimitInit && yObj < yLimitEnd){
			vectObj.erase(vectObj.begin()+i);
			}
	}
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
	Objeto obj = {posicion, tipo};
	vectObj.push_back(obj);
}

int Map::getCantObjects(){
	return vectObj.size();
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

void Map::ordenarObjects(Vector &pos){
	std::vector<Objeto> vectorAux;

	for (Objeto obj : vectObj){
		agregarVectDist(vectorAux, obj, pos);
	}
	vectObj.swap(vectorAux);
}

Vector Map::getPosObj(int &pos){
	Objeto objPedido = vectObj.at(pos);
	return objPedido.posicion;
}

int Map::getTipoObj(int &pos){
	Objeto objPedido = vectObj.at(pos);
	return objPedido.tipoObjecto;	
}

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