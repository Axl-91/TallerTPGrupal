#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Raycaster.h"
#define LONG_SCREEN 320
#define HIGH_SCREEN 200

#define PI 3.14159265358979323846
#define ANGLE_0 0
#define ANGLE_90 90
#define ANGLE_180 180
#define ANGLE_270 270
#define ANGLE_360 360

int toDegreesRay(float rad){
	float degrees = (rad / PI) * 180;
	int degreesInt = round(degrees);
	return degreesInt;
}

Raycaster::Raycaster(Vector &pos, float &anglePlayer, Map &map):
    mapRay(map), posPlayer(pos), angPlayer(anglePlayer), rayH(0,0){
}

void Raycaster::makeRay(float &angle){
	angRay = angle;

	raycasterHorizontal();
    raycasterVertical();
    finalRay();
}

void Raycaster::raycasterHorizontal(){
    float rx=0, ry=0, xo=0, yo=0;
    Vector raySum(0,0);
	bool noCollision = true;
	int degrees = 0;
	degrees = toDegreesRay(angRay);
	float tangH = -1/tan(angRay);
	int longTile = mapRay.getLongTiles();

	if (degrees > ANGLE_180){
		int tilePosition = posPlayer.getY() / longTile;
		ry = tilePosition*longTile - 0.0001;
		rx = (posPlayer.getY() - ry)*tangH + posPlayer.getX();
        rayH.set(rx,ry);

		yo = -longTile;
		xo = -yo*tangH;
        raySum.set(xo,yo);
	}
	if (degrees < ANGLE_180){
		int tilePosition = posPlayer.getY() / longTile;
		ry = tilePosition*longTile + longTile;
		rx = (posPlayer.getY() - ry)*tangH + posPlayer.getX();
        rayH.set(rx,ry);

		yo = longTile;
		xo = -yo*tangH;
        raySum.set(xo,yo);

	}
	if (degrees == ANGLE_0 || degrees == ANGLE_360 || degrees == ANGLE_180){
		noCollision = false;
	}

	while (noCollision){
		distH = posPlayer.getDistance(rayH);

		if (!mapRay.validPosition(rayH)){
			break;
		}
		if (mapRay.getTile(rayH) == 0){
			rayH.add(raySum);
		} else {
			noCollision = false;
		}
	}
}

void Raycaster::raycasterVertical(){
    float rx, ry, xo, yo;
    Vector raySum(0,0);
	bool noCollision = true;
	int degrees = toDegreesRay(angRay);
	float tangV = -tan(angRay);
	int longTile = mapRay.getLongTiles();

	if (degrees < ANGLE_270 && degrees > ANGLE_90){
		int tilePosition = posPlayer.getX() / longTile;
		rx = tilePosition*longTile - 0.0001;
		ry = (posPlayer.getX() - rx)*tangV + posPlayer.getY();
        rayV.set(rx, ry);

		xo = -longTile;
		yo = -xo*tangV;
        raySum.set(xo, yo);
	}
	if (degrees > ANGLE_270 || degrees < ANGLE_90){
		int tilePosition = posPlayer.getX() / longTile;
		rx = tilePosition*longTile + longTile;
		ry = (posPlayer.getX() - rx)*tangV + posPlayer.getY();
        rayV.set(rx, ry);

		xo = longTile;
		yo = -xo*tangV;
        raySum.set(xo, yo);
	}
	if (degrees == ANGLE_270 || degrees == ANGLE_90){
		noCollision=false;
	}

	while (noCollision){
		distV = posPlayer.getDistance(rayV);

		if (!mapRay.validPosition(rayV)){
			break;
		}
		if (mapRay.getTile(rayV) == 0){
			rayV.add(raySum);
		} else {
			noCollision = false;
		}
	}
}

void Raycaster::finalRay(){
    if (distH < distV){
        distT = distH;
        rayFinal = rayH;
		mapRay.setWall(rayFinal, false);
		float rayX = rayFinal.getX();
		mapRay.setColWall(rayX);

    } else{
        distT = distV;
        rayFinal = rayV;
		mapRay.setWall(rayFinal, true);
		float rayY = rayFinal.getY();
		mapRay.setColWall(rayY);
    }
	/* Para evitar efecto fisheye */
	float newAngle = angPlayer - angRay;
	if (newAngle < 0) {newAngle +=2*PI;}
	if (newAngle > 2*PI) {newAngle -= 2*PI;}
	distT = distT * cos(newAngle);
}

float Raycaster::getDistance(){
    return distT;
}

void Raycaster::render(int &pos){
	int largoCol = 1;
	int longTile = mapRay.getLongTiles();
	float largoPared = (longTile * LONG_SCREEN) / distT;
	//Desde donde voy a empezar a dibujar la pared
	float offset = (HIGH_SCREEN/2) - (largoPared/2);

	int largoParedInt = largoPared;
	int offsetInt = offset;
	
	mapRay.renderWall(pos, offsetInt, largoCol, largoParedInt);
}

Raycaster::~Raycaster(){}
