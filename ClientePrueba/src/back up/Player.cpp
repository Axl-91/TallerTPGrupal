#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "Raycaster.h"
#include "weapon_t.h"

#define PLAYER_STEP 5
#define PLAYER_RADIUS 16
#define PLAYER_START_ANGLE 0

int toGrados(float radiales){
	float anguloGrados = (radiales / PI) * 180;
	int anguloInt = round(anguloGrados);
	return anguloInt;
}

Player::Player(Map &m): mapPlayer(m),
currentWeapon(inventory.getWeapon(currentWeapon, 1)){
	angulo = PLAYER_START_ANGLE;
    dx = cos(angulo);
    dy = sin(angulo);
	position.radius=PLAYER_RADIUS;
	step=PLAYER_STEP;
}


weapon_t Player::equip(weapon_t w){
	w=inventory.equip(w);
	setWeapon(WP_SECONDARY);
	return w;
}

void Player::setPos(float x, float y){
    position.x = x;
    position.x = y;
}


void Player::setRenderer(SDL_Renderer* renderer){
	hudGame.setRenderer(renderer);
	inventory.setRenderer(renderer);
    rendererPlayer = renderer;
}


void Player::setDirection(float x, float y){
	dx=x;
	dy=y;
}


void Player::move(player_orientation_t &orientation){
	position.x+=dx*orientation;
	position.y+=dy*orientation;
	setDirection(step*cos(angulo), step*sin(angulo));
}



// void Player::avanzar(){
// 	position.x+=dx;
// 	position.y+=dy;
// 	setDirection(step*cos(angulo), step*sin(angulo));
// }

// void Player::retroceder(){
// 	position.x-=dx;
// 	position.y-=dy;
// 	setDirection(step*cos(angulo), step*sin(angulo));
// }

void Player::setWeapon(int w){
	if(w<1 || w>WEAPONS)
		return;

	currentWeapon=inventory.getWeapon(currentWeapon,w);
	hudGame.setWeapon(currentWeapon->getType());
}

void Player::rotateLeft(){
	angulo -= PI/36;
	if (toGrados(angulo) < 0){
		angulo += 2*PI;
	}
	dx = step*cos(angulo);
	dy = step*sin(angulo);
}


void Player::rotateRight(){
	angulo += PI/36;
	if (toGrados(angulo) >= 360){
		angulo -= 2*PI;
	}
	dx = step*cos(angulo);
	dy = step*sin(angulo);
}


void Player::getPosition(circle &c){
	c.x=position.x;
	c.y=position.y;
	c.radius=position.radius;
}


void Player::getPosition(float &x, float &y){
	x=position.x;
	y=position.y;
}

void Player::getDirection(float &x, float &y){
	x=dx;
	y=dy;
}

void Player::shoot(){
	currentWeapon->shoot();
}


void Player::renderRaycaster(){
	Vector vectorPos(position.x, position.y);
	Raycaster raycaster(vectorPos, angulo, mapPlayer);
	float anguloRay = angulo-PI/6;

	for (int pos=0; pos < 320; ++pos){

		if (anguloRay < 0){
			anguloRay += 2*PI;
		} else if (anguloRay > 2*PI){
			anguloRay -=2*PI;
		}
		raycaster.crearRay(anguloRay);
		raycaster.render(pos);
		distBuffer[pos] = raycaster.getDistancia();
		anguloRay += PI/960;
	}
}

bool Player::objEsVisible(Vector &posObj){
	/*Visibilidad hacia izq y derecha en radiales
	serian 30 grados pero agrego 5 mas para que
	se vea mas el sprite del objeto */
	float gVis = 35.0/180.0;
	float visible = PI * gVis;

	float dx = posObj.getX() - position.x;
	float dy = posObj.getY() - position.y;

	float anguloObj = atan2(dy, dx);
	float difAng = angulo - anguloObj;

	if (difAng < -PI){
		difAng += 2*PI;
	}
	if (difAng > PI){
		difAng -= 2*PI;
	}
	bool res = (difAng < visible);
	res &= (difAng > -visible);

	return res;
}

void Player::renderObjects(){
	int uno = 1;
	Vector posJugador = Vector(position.x, position.y);
	mapPlayer.ordenarObjects(posJugador);
	
	for (int obj = 0; obj < mapPlayer.getCantObjects(); ++obj){
		Vector posObjeto = mapPlayer.getPosObj(obj);
		if (!objEsVisible(posObjeto)){
			continue;
		}
		int tipoObj = mapPlayer.getTipoObj(obj);
		float distanciaObj = posJugador.distancia(posObjeto);

		//Coordenadas en Y
		float sizeObj = (64 * 320) / distanciaObj;
		float yo = 100 - (sizeObj/2);
		//Coordenadas en X
		float dx = position.x - posObjeto.getX();
		float dy = position.y - posObjeto.getY();

		float anguloObj = atan2(dy, dx) - angulo;
		float xo = tan(anguloObj) * 277.1281;
		float x = round((320/2) + xo - (sizeObj/2));

		float anchura = sizeObj / 64;
		int yoInt = yo;
		int sizeObjInt = sizeObj;
		mapPlayer.setObj(tipoObj);

		for (int i = 0; i < 64; ++i){
			for (int j = 0; j < anchura; ++j){
				int z = round(x)+((i)*anchura)+j;
				if (z < 0 || z > 320){ continue; }

				if (distBuffer[z] > distanciaObj){
					mapPlayer.setColObject(i);
					mapPlayer.renderObject(z, yoInt, uno, sizeObjInt);
				}
			}
		}
	}
}

void Player::render(int largoWin, int altoWin){
	renderRaycaster();
	renderObjects();
	currentWeapon->render(largoWin, altoWin);
	hudGame.render(largoWin, altoWin);

}

Player::~Player(){}