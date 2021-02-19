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
#include "enemies/Enemies.h"

#include "../common_src/types.h"

typedef struct Object_t {
	Vector position;
	int objType;
} Object_t;

class Map{
private:
	int longTile = 64;
	int rows;
	int cols;
	std::vector<std::vector<int>> map;

	Walls walls;
	Objects objects;
	Enemies enemies;

	std::map<int, Enemy_t> mapEnemies;

	std::map<std::pair<int,int>, Object_t> mapDoors;
	std::map<std::pair<int,int>, Object_t> mapObj;
public:
	Map(std::vector<std::vector<int>> &lvl);
	~Map();

	void insertWeaponWithCoords(int j, int i, int obj);
	void insertObject(int x, int y, int obj);
	void insertEnemy(Player_t &p);
	std::map<int, Enemy_t>& getEnemies();
	void load(std::vector<std::vector<int>> lvl);
	void setRenderer(SDL_Renderer* renderer);
	int getLongTiles();
	bool validPosition(float &x, float &y);
	bool validPosition(Vector &pos);
	int getTile(float &x, float &y);
	int getTile(Vector &pos);
	void setWall(Vector &pos, bool dark);
	void setColWall(float &pos);
	void renderWall(int &posX, int &posY, int &lenght, int &height);
	void addObject(Vector &pos, int type);
	std::vector<Object_t> orderObjects(Vector &pos);
	void eraseObj(float x, float y);
	void setObj(int &pos);
	void renderEnemy(int &posX, int &posY, int &lenght, int &height);
	void setColEnemy(int &pos);
	void setColObject(int &pos, int type);
	void renderObject(int &posX, int &posY, int &lenght, int &height, int type);
	void update(Map_change_t &aMapChange);
	void updateEnemy(Player_t &p);


	void insertDoor(int x, int y, int doorType);
	void openDoor(int x, int y);

};

#endif
