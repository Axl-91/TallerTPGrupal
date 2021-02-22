#ifndef __SV_MAP__
#define __SV_MAP__

#include <iostream>
#include <vector>
#include <map>
#include "../common_src/Vector.h"

#include "../common_src/types.h"

typedef struct Object_t {
	Vector position;
	int objType;
} Object_t;

class svMap{
private:
	int longTile = 64;
	int rows;
	int cols;
	std::vector<std::vector<int>> map;
	std::map<std::pair<int,int>, Object_t> mapObj;
public:
	svMap(std::vector<std::vector<int>> &lvl);
	~svMap();

	void load(std::vector<std::vector<int>> lvl);
	int getLongTiles();
	bool validPosition(float &x, float &y);
	bool validPosition(Vector &pos);
	std::vector<Object_t> orderObjects(Vector &pos);
	
	void insertObject(int x, int y, int obj);
	int getTile(float &x, float &y);
	int getTile(Vector &pos);
};

#endif
