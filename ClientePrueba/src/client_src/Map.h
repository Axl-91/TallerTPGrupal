#ifndef __MAP__
#define __MAP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <map>
// #include <utility>
#include "../common_src/Vector.h"
#include "Walls.h"
#include "Objects.h"
#include "Enemies.h"

#include "../common_src/types.h"

typedef struct Objeto {
	Vector posicion;
	int tipoObjecto;
} Objeto;

class Map{
private:
	int largoBloque = 64;
	int rows;
	int cols;
	std::vector<std::vector<int>> map;

	Walls walls;
	Objects objects;
	Enemies enemies;

	std::map<int, Player_t> mapEnemies;
	std::map<std::pair<int,int>, Objeto> mapObj;
public:
	Map(std::vector<std::vector<int>> &lvl);
	~Map();

	void insertWeaponWithCoords(int j, int i, int obj);
	void insertObject(int x, int y, int obj);
	void insertEnemy(Player_t &p);
	std::map<int, Player_t>& getEnemies();
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
	std::vector<Objeto> ordenarObjects(Vector &pos);
	// int getCantObjects();
	void eraseObj(float x, float y);
	// Vector getPosObj(int &pos);
	// int getTipoObj(int &pos);
	void setObj(int &pos);
	void renderEnemy(int &posX, int &posY, int &largo, int &alto);
	void setColEnemy(int &pos);

	void setColObject(int &pos, int type);
	// void setColObject(int &pos);
	void renderObject(int &posX, int &posY, int &largo, int &alto, int type);
	// void renderObject(int &posX, int &posY, int &largo, int &alto);
	void update(Map_change_t &aMapChange);
	void updateEnemy(Player_t &p);
};

#endif
