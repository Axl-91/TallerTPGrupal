#include "ShootingRaycaster.h"


int stoGradosRay(float radiales){
	float angulo = (radiales / PI) * 180;
	int anguloInt = round(angulo);
	return anguloInt;
}

ShootingRaycaster::ShootingRaycaster(Vector &pos, float &anguloPlayer, CollisionMap &map):
    mapRay(map), posPlayer(pos), angPlayer(anguloPlayer), rayH(0,0){
}

ShootingRaycaster::~ShootingRaycaster(){}


void ShootingRaycaster::crearRay(float &angulo){
	angRay = angulo;

	raycasterHorizontal();
    raycasterVertical();
    calcularRayFinal();
}

void ShootingRaycaster::raycasterHorizontal(){
    float rx=0, ry=0, xo=0, yo=0;
    Vector raySuma(0,0);
	bool noHayColision = true;
	int grados = 0;
	grados = stoGradosRay(angRay);
	float tangH = -1/tan(angRay);
	int largoBloque = mapRay.getLongBloques();

	if (grados > 180){
		int bloqPasados = posPlayer.getY() / largoBloque;
		ry = bloqPasados*largoBloque - 0.0001;
		rx = (posPlayer.getY() - ry)*tangH + posPlayer.getX();
        rayH.set(rx,ry);

		yo = -largoBloque;
		xo = -yo*tangH;
        raySuma.set(xo,yo);
	}
	if (grados < 180){
		int bloqPasados = posPlayer.getY() / largoBloque;
		ry = bloqPasados*largoBloque + largoBloque;
		rx = (posPlayer.getY() - ry)*tangH + posPlayer.getX();
        rayH.set(rx,ry);

		yo = largoBloque;
		xo = -yo*tangH;
        raySuma.set(xo,yo);

	}
	if (grados == 0 || grados == 360 || grados == 180){
		noHayColision = false;
	}

	while (noHayColision){
		distH = posPlayer.distancia(rayH);

		if (!mapRay.hayCoordenadas(rayH)){
			break;
		}
		if (mapRay.getBloque(rayH) == 0){
			rayH.sumar(raySuma);
		} else {
			noHayColision = false;
		}
	}
}

void ShootingRaycaster::raycasterVertical(){
    float rx, ry, xo, yo;
    Vector raySuma(0,0);
	bool noHayColision = true;
	int grados = stoGradosRay(angRay);
	float tangV = -tan(angRay);
	int largoBloque = mapRay.getLongBloques();

	if (grados < 270 && grados > 90){
		int bloqPasados = posPlayer.getX() / largoBloque;
		rx = bloqPasados*largoBloque - 0.0001;
		ry = (posPlayer.getX() - rx)*tangV + posPlayer.getY();
        rayV.set(rx, ry);

		xo = -largoBloque;
		yo = -xo*tangV;
        raySuma.set(xo, yo);
	}
	if (grados > 270 || grados < 90){
		int bloqPasados = posPlayer.getX() / largoBloque;
		rx = bloqPasados*largoBloque + largoBloque;
		ry = (posPlayer.getX() - rx)*tangV + posPlayer.getY();
        rayV.set(rx, ry);

		xo = largoBloque;
		yo = -xo*tangV;
        raySuma.set(xo, yo);
	}
	if (grados == 270 || grados == 90){
		noHayColision=false;
	}

	while (noHayColision){
		distV = posPlayer.distancia(rayV);

		if (!mapRay.hayCoordenadas(rayV)){
			break;
		}
		if (mapRay.getBloque(rayV) == 0){
			rayV.sumar(raySuma);
		} else {
			noHayColision = false;
		}
	}
}

void ShootingRaycaster::calcularRayFinal(){
    if (distH < distV){
        distT = distH;
        rayFinal = rayH;
		float rayX = rayFinal.getX();

    } else{
        distT = distV;
        rayFinal = rayV;
		float rayY = rayFinal.getY();
    }
	float angNuevo = angPlayer - angRay;
	if (angNuevo < 0) {angNuevo +=2*PI;}
	if (angNuevo > 2*PI) {angNuevo -= 2*PI;}
	distT = distT * cos(angNuevo);
}

float ShootingRaycaster::getDistancia(){
    return distT;
}
