#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "Raycaster.h"
#include "../common_src/types.h"

#define PLAYER_STEP 5
#define PLAYER_RADIUS 16
#define PLAYER_START_ANGLE 0

#define LONG_SCREEN 320
#define HIGH_SCREEN 200

Player::Player(Map &m): 
	mapPlayer(m),
	inventory(shootingState),
	currentWeapon(inventory.getWeapon(currentWeapon, WP_KNIFE))
{
	// health=MAX_HEALTH;
	health = 50;
	angPlayer = PLAYER_START_ANGLE;
    dx = cos(angPlayer);
    dy = sin(angPlayer);
	position.radius = PLAYER_RADIUS;
	step = PLAYER_STEP;
	goldKey = false;
	blueKey = false;
}

void Player::equip(weapon_t w){
	if(inventory.equip(w) == true);
		setWeapon(WP_SECONDARY);
}

void Player::setPos(float x, float y){
    position.x = x;
    position.y = y;
}

void Player::setRenderer(SDL_Renderer* renderer){
	hudGame.setRenderer(renderer);
	inventory.setRenderer(renderer);
    rendererPlayer = renderer;
}

void Player::setDirection(float x, float y){
	dx = x;
	dy = y;
}

void Player::setWeapon(player_weapons_t aWeapon){
	if(aWeapon < 1 || aWeapon > MAX_WEAPONS)
		return;

	currentWeapon = inventory.getWeapon(currentWeapon, aWeapon);
	hudGame.setWeapon(currentWeapon->getType());
}

void Player::getPosition(circle &c){
	c.x = position.x;
	c.y = position.y;
	c.radius = position.radius;
}

void Player::getPosition(float &x, float &y){
	x = position.x;
	y = position.y;
}

void Player::getDirection(float &x, float &y){
	x = dx;
	y = dy;
}

void Player::renderRaycaster(){
	Vector vectorPos(position.x, position.y);
	Raycaster raycaster(vectorPos, angPlayer, mapPlayer);
	float angleRay = angPlayer - PI/6;

	for (int pos=0; pos < LONG_SCREEN; ++pos){

		if (angleRay < 0){
			angleRay += 2*PI;
		} else if (angleRay > 2*PI){
			angleRay -=2*PI;
		}
		raycaster.makeRay(angleRay);
		raycaster.render(pos);
		distBuffer[pos] = raycaster.getDistance();
		angleRay += PI/960;
	}
}

void Player::setID(size_t newID){
	ID = newID;
}

void Player::shoot(){
	currentWeapon->shoot(shootingState);
}

void Player::renderObjects(){
	int one = 1;
	Vector posPlayer = Vector(position.x, position.y);
	std::vector<Object_t> orderedObjets;
	orderedObjets = mapPlayer.orderObjects(posPlayer);

	for (int obj = 0; obj < orderedObjets.size(); ++obj){
		Vector posObjeto = orderedObjets[obj].position;
		if (!objIsVisible(posObjeto)){
			continue;
		}
		// int tipoObj = mapPlayer.getTipoObj(obj);
		int typeObj = orderedObjets[obj].objType;

		int longTiles = mapPlayer.getLongTiles();
		float distObj = posPlayer.getDistance(posObjeto);

		//Coordenadas en Y
		float sizeObj = (longTiles * LONG_SCREEN) / distObj;
		float yo = (HIGH_SCREEN/2) - (sizeObj/2);
		//Coordenadas en X
		float dx = position.x - posObjeto.getX();
		float dy = position.y - posObjeto.getY();

		float angObj = atan2(dy, dx) - angPlayer;
		float distProyPlane = (LONG_SCREEN/2) / tan(PI/6);
		float xo = tan(angObj) * distProyPlane;
		float x = round((LONG_SCREEN/2) + xo - (sizeObj/2));

		float longObj = sizeObj / longTiles;
		int yoInt = yo;
		int sizeObjInt = sizeObj;
		mapPlayer.setObj(typeObj);

		for (int i = 0; i < longTiles; ++i){
			for (int j = 0; j < longObj; ++j){
				int z = round(x)+((i)*longObj)+j;
				if (z < 0 || z > LONG_SCREEN){ continue; }

				if (distBuffer[z] > distObj){
					mapPlayer.setColObject(i,orderedObjets[obj].objType);
					mapPlayer.renderObject(z, yoInt, one, sizeObjInt,orderedObjets[obj].objType);
				}
			}
		}
	}
}

void Player::updateInfo(Player_t &p){
	position.x = p.x;
	position.y = p.y;
	angPlayer = p.ang;
	lifes = p.lifes;
	score = p.score;
	ammo = p.ammo;
	health = p.health;
	equip(p.secondaryWP);
    blueKey = p.blueKey;
    goldKey = p.goldKey;   
	dead = p.dead;
	lost = p.lost;
	setWeapon(p.currentWP);
	shootingState = p.shootingState;

	currentWeapon->shoot(shootingState);
	mapPlayer.getPointsVector(ID, score);
}

size_t Player::getID(){
	return ID;
}

void Player::render(int largoWin, int altoWin){
	renderRaycaster();
	renderObjects();
	currentWeapon->render(largoWin, altoWin);
	hudGame.render(largoWin, altoWin);
	hudGame.renderHealth(health);
	hudGame.renderLife(lifes);
	hudGame.renderAmmo(ammo);
	hudGame.renderScore(score);
	if(goldKey == true)
		hudGame.renderGoldenKey();
    if(blueKey == true)
		hudGame.renderSilverKey();
}

bool Player::objIsVisible(Vector &posObj){
	/*Visibilidad hacia izq y derecha en radiales
	serian 30 grados pero agrego 5 mas para que
	se vea mas el sprite del objeto */
	float gVis = 35.0/180.0;
	float visible = PI * gVis;

	float dx = posObj.getX() - position.x;
	float dy = posObj.getY() - position.y;

	float angleObj = atan2(dy, dx);
	float difAng = angPlayer - angleObj;

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


Player::~Player(){}