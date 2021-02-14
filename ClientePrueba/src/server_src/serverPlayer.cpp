#include "serverPlayer.h"
#include <iostream>
#include "../common_src/types.h"


#define SHOOTING_ANGLE 0.087263
#define COEF_SHOOTING_DISTANCE_DIVISOR 512
#define COEF_SHOOTING_DISTANCE_OFFSET 0.2
#define SHOOTING_SIZE 20
#define COEF_SHOOTING_ANGLE_DIVISOR 96

//funcion para debugear
int toGrados(float radiales){
	float anguloGrados = (radiales / PI) * 180;
	int anguloInt = round(anguloGrados);
	return anguloInt;
}


ServerPlayer::ServerPlayer(float x, float y, float a, size_t newID):
currentWeapon(inventory.getWeapon(currentWeapon, WP_KNIFE))
{
	init_posx = x;
	init_posy = y;
    position.x=x;
    position.y=y;
    position.radius=16;
    ang=a;
    step=5;
	dirx = step*cos(ang);
	diry = step*sin(ang); 
	currentWP = WP_KNIFE;
	health = 50;
	ammo = 50;
	key = false;
	shootingState = SHOOTING_STATE_QUIET;
	// shooting = false;
	lifes = 3;
	score = 0;
	moveOrientation = MOVE_QUIET;
	rotateOrientation = ROTATE_QUIET;
	ID = newID;
	updateAvailable=true;
}
ServerPlayer::~ServerPlayer(){}

ServerPlayer::ServerPlayer(ServerPlayer&& other):
	inventory(std::move(other.inventory)),
	currentWeapon(inventory.getWeapon(currentWeapon, WP_KNIFE))
{
	init_posx = other.init_posx;
	init_posy = other.init_posy;
	position = other.position;
    ang=other.ang;
    step=other.step;
	dirx = other.dirx;
	diry = other.diry;
	currentWP = other.currentWP;
	health = other.health;
	ammo = other.ammo;
	key = other.key;
	// shooting = false;
	shootingState = other.shootingState;
	lifes = other.lifes;
	score = other.score;
	moveOrientation = other.moveOrientation;
	rotateOrientation = other.rotateOrientation;
	ID = other.ID;
}
// void ServerPlayer::setID(size_t newID){
// 	ID = newID;
// }


bool ServerPlayer::updateIsAvailable(){
	return updateAvailable;
}

void ServerPlayer::updated(){
	updateAvailable=false;
}

void ServerPlayer::respawn(){
	position.x = init_posx;
	position.y = init_posy;
}

void ServerPlayer::rotate(){
	ang -= PI/36*rotateOrientation;
	if (ang < 0 || ang >= 2*PI){
		ang += 2*PI*rotateOrientation;
	}
	if(rotateOrientation!=ROTATE_QUIET)
		updateAvailable=true;

	dirx = step*cos(ang);
	diry = step*sin(ang);
}

void ServerPlayer::move(){
	position.x+=dirx*moveOrientation;
	position.y+=diry*moveOrientation;
	if(moveOrientation!=MOVE_QUIET)
		updateAvailable=true;

	setDirection(step*cos(ang), step*sin(ang));
}

void ServerPlayer::setDirection(float x, float y){
	dirx=x;
	diry=y;
}

void ServerPlayer::setCurrentWeapon(player_weapons_t aWeapon){
	if(aWeapon < 1 || aWeapon > MAX_WEAPONS)
		return;

	updateAvailable=true;
	currentWP=aWeapon;
	currentWeapon=inventory.getWeapon(currentWeapon, aWeapon);
}

void ServerPlayer::setMoveOrientation(player_move_orientation_t o){
	moveOrientation = o;
}
void ServerPlayer::seteRotateOrientation(player_rotate_orientation_t o){
	rotateOrientation = o;
}

void ServerPlayer::startShooting(){
	currentWeapon->shootingTrue();
	shootingState = SHOOTING_STATE_STARTED;
	// shooting = true;
}

void ServerPlayer::stopShooting(){
	shootingState = SHOOTING_STATE_QUIET;

	// shooting = false;
}

weapon_t ServerPlayer::equip(weapon_t weapon){
	weapon_t last;
	updateAvailable=true;
	if((last=inventory.equip(weapon))!=NONE);
		setCurrentWeapon(WP_SECONDARY);

	return last;
}

//Usa trigonometria para definir la proporcion de daño que le sacara al enemigo
//de acuerdo a la distancia (ad=adyacente) y angulo (op=opuesto)
void ServerPlayer::getDamageCoefficient(ServerPlayer &enemy, float &coef, float wallDist){
	float eX;
	float eY;
	enemy.getPosition(eX,eY);
	Vector enemyPos(eX,eY);
	Vector pos(position.x, position.y);
	float distance = pos.distancia(enemyPos); 
	float anguloObj = pos.getAngle(enemyPos);
	float difAng = ang - anguloObj;

	if (difAng < -PI){
		difAng += 2*PI;
	}
	if (difAng > PI){
		difAng -= 2*PI;
	}
	if(difAng<0)
		difAng=-difAng;
	//se forma un triangulo rectangulo con posicion del jugador,
	//direccion de tiro y posicion del enemigo
	float op=sin(difAng)*distance; //cateto opuesto
	float ad=cos(difAng)*distance; //cateto adyacente
	if(ad>wallDist || op > SHOOTING_SIZE){
		coef=0;
		return;
	}
	float coefDistance = COEF_SHOOTING_DISTANCE_OFFSET+exp(-ad/COEF_SHOOTING_DISTANCE_DIVISOR);
	float coefAng= exp(-op/COEF_SHOOTING_ANGLE_DIVISOR);
	coef=coefDistance*coefAng;
	if(coef>1)
		coef=1;

}

void ServerPlayer::shoot(ServerPlayer &enemy, float coef){
	float weaponDamage;
	int totalDamage;
	weaponDamage = currentWeapon->shoot(this->getDist(enemy), shootingState);
	weaponDamage *= coef;
	totalDamage = (int) weaponDamage;
	enemy.beDamaged(totalDamage);
}


float ServerPlayer::getDist(ServerPlayer &enemy){
	Vector pPos(position.x, position.y);
	Vector ePos(enemy.position.x, enemy.position.y);

	return pPos.distancia(ePos)-2*position.radius;
}


void ServerPlayer::beDamaged(int damage){
	health-=damage;
	updateAvailable=true;
	if(health <= 0){
		respawn();
		health = 100;
		lifes -= 1;
		if(lifes <= 0){
			lifes = 0;
			// logica muerte
		}
			
	}
}



// bool ServerPlayer::startedShooting(){
// 	if(shootingState != SHOOTING_STATE_QUIET){
// 		updateAvailable = true;
// 		return true;
// 	}
// 	return false;
// }

size_t ServerPlayer::getID(){
	return ID;
}

float ServerPlayer::getAngle(){
	return ang;
}

int ServerPlayer::heal(int h){
	if(health>=MAX_HEALTH)
		return 0;
	updateAvailable=true;

	health=health+h;
	if(health>MAX_HEALTH)
		health=MAX_HEALTH;

	return 1;
}

int ServerPlayer::grabKey(game_key_t k){
	if(key==true)
		return 0;
	key=true;
	return 1;
}

int ServerPlayer::addPoints(int p){
	score+=p;
	return 1;
}

int ServerPlayer::reload(int a){
	if(ammo>=MAX_AMMO)
		return 0;

	updateAvailable=true;
	ammo+=a;
	if(ammo>MAX_AMMO)
		ammo=MAX_AMMO;

	return 1;
}
void ServerPlayer::getPlayerInfo(Player_t &p){
    p.x = position.x;
    p.y = position.y;
    p.ang = ang;
    p.dirx = dirx;
    p.diry = diry;
	p.currentWP = currentWP;
	p.secondaryWP = getSecondaryWPtype();
	p.moving = moveOrientation;
	p.rotating = rotateOrientation;
	p.ammo = ammo;
	p.health = health;
	p.lifes = lifes;
	p.score = score;
	p.key = key;
	p.shootingState = shootingState;
	p.ID = ID;
    p.step = step;
}

player_move_orientation_t ServerPlayer::getMoveOrientation(){
	return moveOrientation;
}

weapon_t ServerPlayer::getSecondaryWPtype(){
	return inventory.getSecondaryWPtype();
}


void ServerPlayer::getPosition(circle &c){
	c.x=position.x;
	c.y=position.y;
	c.radius=position.radius;
}


void ServerPlayer::getPosition(float &x, float &y){
	x=position.x;
	y=position.y;
}

void ServerPlayer::getDirection(float &x, float &y){
	x=dirx;
	y=diry;
}

// void ServerPlayer::shoot(){
// 	currentWeapon->shoot();
// }

bool ServerPlayer::isShooting(){
		updateAvailable=true;

	if(shootingState != SHOOTING_STATE_QUIET){
		// updateAvailable=true;
		return true;
	}
	return false;
}
