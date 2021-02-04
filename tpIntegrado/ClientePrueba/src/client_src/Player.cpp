#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Player.h"
#include "Raycaster.h"
#include "../common_src/types.h"

#define PLAYER_STEP 5
#define PLAYER_RADIUS 16
#define PLAYER_START_ANGLE 0
//10*PI/180=0.1745
// #define SHOOTING_ANGLE 0.1745
#define SHOOTING_ANGLE 0.087263
#define COEF_SHOOTING_DISTANCE_DIVISOR 512
#define COEF_SHOOTING_DISTANCE_OFFSET 0.2
#define SHOOTING_SIZE 20
#define COEF_SHOOTING_ANGLE_DIVISOR 96

float toGrados(float radiales){
	// float anguloGrados = (radiales / PI) * 180;
	// int anguloInt = round(anguloGrados);
	return (radiales / PI) * 180;
}
Player::Player(Map &m): 
	mapPlayer(m),//,
	// currentWeapon(inventory.getWeapon(currentWeapon, KNIFE))
	currentWeapon(inventory.getWeapon(currentWeapon, WP_KNIFE))
{
	// health=MAX_HEALTH;
	health=50;
	angulo = PLAYER_START_ANGLE;
    dx = cos(angulo);
    dy = sin(angulo);
	position.radius=PLAYER_RADIUS;
	step=PLAYER_STEP;
}
float toRandians(float grades){
	return grades*PI/180;	
}


void Player::equip(weapon_t w){
	if(inventory.equip(w)==true);
		setWeapon(WP_SECONDARY);
}
/*
int Player::heal(int h){
	if(health>=MAX_HEALTH)
		return 0;
	std::cout<<"health before: "<<health<<std::endl;

	health=health+h;
	if(health>MAX_HEALTH)
		health=MAX_HEALTH;
	std::cout<<"health after: "<<health<<std::endl;

	// hudGame.setHealth(health);
	return 1;
}

int Player::reload(int ammo){
	int used=inventory.reload(ammo);
	// hudGame.setAmmo(ammo);

	return used;
}
*/
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
	dx=x;
	dy=y;
}



void Player::setWeapon(player_weapons_t aWeapon){
	if(aWeapon < 1 || aWeapon > MAX_WEAPONS)
		return;

	currentWeapon=inventory.getWeapon(currentWeapon, aWeapon);
	hudGame.setWeapon(currentWeapon->getType());
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

void Player::shootRaycaster(){
	Vector vectorPos(position.x, position.y);
	Raycaster raycaster(vectorPos, angulo, mapPlayer);
	float anguloRay = angulo;
	if (anguloRay < 0){
		anguloRay += 2*PI;
	} else if (anguloRay > 2*PI){
		anguloRay -=2*PI;
	}

	raycaster.crearRay(anguloRay);
	shootRay=raycaster.getDistancia();
}

bool Player::enemyInShootRange(Vector &posObj){
	// Visibilidad hacia izq y derecha en radiales
	// serian 30 grados pero agrego 5 mas para que
	// se vea mas el sprite del objeto 
	

	// float gVis = SHOOTING_ANGLE/180.0;
	// float visible = PI * gVis;
	float visible = SHOOTING_ANGLE;

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

void Player::setID(size_t newID){
	ID = newID;
}

void Player::shoot(){
	std::map<int, Player_t>& enemies = mapPlayer.getEnemies();
	float damageCoef;
	Vector enemyPos;

	for(auto e: enemies){
		Vector pos(e.second.x, e.second.y);

		enemyPos = pos;
		
		// if(enemyInShootRange(enemyPos)==false)
		// 	continue;
		getDamageCoefficient(enemyPos, damageCoef);
				// if(damageCoef!=0)
		// 	currentWeapon->getDamage(enemyPos, damageCoef)
		std::cout<<"coeficiente: "<<damageCoef<<std::endl;
	}

	currentWeapon->shoot();
}

void Player::getDamageCoefficient(Vector &enemyPos, float &coef){
	std::cout<<"getDamageCoefficient-------------------------------------------------------------- "<<std::endl;
	Vector pos(position.x, position.y);
	
	float distance = pos.distancia(enemyPos); 


	float anguloObj = pos.getAngle(enemyPos);
	
	// std::cout<<"anguloObj: "<<toGrados(anguloObj)<<std::endl;
	float difAng = angulo - anguloObj;

	if (difAng < -PI){
		difAng += 2*PI;
	}
	if (difAng > PI){
		difAng -= 2*PI;
	}
	if(difAng<0)
		difAng=-difAng;

	std::cout<<"difAng: "<<toGrados(difAng)<<std::endl;

	//se forma un triangulo rectangulo con posicion del jugador,
	//direccion de tiro y posicion del enemigo
	float op=sin(difAng)*distance; //cateto opuesto
	float ad=cos(difAng)*distance; //cateto adyacente
	shootRaycaster();

	if(ad>shootRay || op > SHOOTING_SIZE){
		coef=0;
		return;
	}
	float coefDistance= COEF_SHOOTING_DISTANCE_OFFSET+exp(-ad/COEF_SHOOTING_DISTANCE_DIVISOR);

	float coefAng= exp(-op/COEF_SHOOTING_ANGLE_DIVISOR);
		std::cout<<"coefDistance: "<<coefDistance<<std::endl;
	std::cout<<"coefAng: "<<coefAng<<std::endl;
	coef=coefDistance*coefAng;
	if(coef>1)
		coef=1;
}

void Player::renderObjects(){
	int uno = 1;
	Vector posJugador = Vector(position.x, position.y);
	std::vector<Objeto> orderedObjets;
	orderedObjets=mapPlayer.ordenarObjects(posJugador);
	

	for (int obj = 0; obj < orderedObjets.size(); ++obj){
		Vector posObjeto = orderedObjets[obj].posicion;
		if (!objEsVisible(posObjeto)){
			continue;
		}
		// int tipoObj = mapPlayer.getTipoObj(obj);
		int tipoObj = orderedObjets[obj].tipoObjecto;

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
					mapPlayer.setColObject(i,orderedObjets[obj].tipoObjecto);
					mapPlayer.renderObject(z, yoInt, uno, sizeObjInt,orderedObjets[obj].tipoObjecto);
				}
			}
		}
	}
}

void Player::updateInfo(Player_t &p){
	position.x = p.x;
	position.y = p.y;
	angulo = p.ang;
    // std::cout<<"el angulo propio: " << angulo*180/3.1415 <<std::endl;
	
	lifes = p.lifes;
	score = p.score;
	inventory.setAmmo(p.ammo);
	health = p.health;
	// ammo = p.ammo;
	equip(p.secondaryWP);
	// if(p.secondaryWP == NONE)
		// std::cout << "El secondaryWP es: " << p.secondaryWP << std::endl;
	setWeapon(p.currentWP);
	// std::cout << "El currentWP es: " << p.currentWP << std::endl;
	if(p.shooting){
		currentWeapon->shoot();
	}
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
	hudGame.renderAmmo(inventory.getAmmo());
	hudGame.renderScore(score);
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


Player::~Player(){}