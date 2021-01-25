#ifndef __MAP__
#define __MAP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
// #include <map>
// #include <utility>
#include "Vector.h"
#include "Walls.h"
#include "Objects.h"

// #define MAP_ROWS 15
// #define MAP_COLS 20

typedef struct Objeto {
	Vector posicion;
	int tipoObjecto;
} Objeto;

class Map{
private:
	int largoBloque = 64;
	int rows;
	int cols;
    //El mapa deberia ser de dimensiones variables
	// int map[MAP_ROWS][MAP_COLS];
	std::vector<std::vector<int>> map;

	Walls walls;
	Objects objects;
	// std::map<std::pair<int,int>, Objeto> mapObj;
	std::vector<Objeto> vectObj;
public:
	Map(std::vector<std::vector<int>> &lvl);
	~Map();

	void insertWeapon(int j, int i, int obj);
	void load(std::vector<std::vector<int>> lvl);
	void setRenderer(SDL_Renderer* renderer);
	int getLongBloques();
	bool hayCoordenadas(float &x, float &y);
	bool hayCoordenadas(Vector &posicion);
	int getBloque(float &x, float &y);
	int getBloque(Vector &posicion);
	void setWall(Vector &posicion, bool dark);
	void setColWall(float &pos);
	void renderWall(int &posX, int &posY, int &largo, int &alto);
	void addObject(Vector &posicion, int tipo);
	void ordenarObjects(Vector &pos);
	int getCantObjects();
	void eraseObj(float x, float y);
	Vector getPosObj(int &pos);
	int getTipoObj(int &pos);
	void setObj(int &pos);
	void setColObject(int &pos);
	void renderObject(int &posX, int &posY, int &largo, int &alto);
};

#endif
