#include "serverPlayer.h"
#include <iostream>
#include "../common_src/types.h"


#define COEF_SHOOTING_DISTANCE_DIVISOR 512
#define COEF_SHOOTING_DISTANCE_OFFSET 0.2
#define SHOOTING_SIZE 20
#define COEF_SHOOTING_ANGLE_DIVISOR 96
#define INITIAL_PLAYER_AMMO 8
#define TIME_TO_RESPAWN 2000
#define MAX_BLOOD_HEAL_PLAYER 10


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
    position.x = x;
    position.y = y;
    position.radius = 16;
    ang = a;
    step = 5;
	dirx = step * cos(ang);
	diry = step * sin(ang); 
	currentWP = WP_KNIFE;
	health = 50;
	ammo = 50;
	blueKey = false;
	goldKey = false;
	shootingState = SHOOTING_STATE_QUIET;
	dead = false;
	lost = true;
	lifes = 3;
	score = 0;
	moveOrientation = MOVE_QUIET;
	rotateOrientation = ROTATE_QUIET;
	ID = newID;
	updateAvailable = true;
	openingDoor = false;

}
ServerPlayer::~ServerPlayer(){}

ServerPlayer::ServerPlayer(ServerPlayer&& other):
	inventory(std::move(other.inventory)),
	currentWeapon(inventory.getWeapon(currentWeapon, WP_KNIFE))
{
	init_posx = other.init_posx;
	init_posy = other.init_posy;
	position = other.position;
    ang = other.ang;
    step = other.step;
	dirx = other.dirx;
	diry = other.diry;
	currentWP = other.currentWP;
	health = other.health;
	ammo = other.ammo;
	blueKey = other.blueKey;
	goldKey = other.goldKey;
	dead = other.dead;
	lost = other.lost;
	shootingState = other.shootingState;
	lifes = other.lifes;
	score = other.score;
	moveOrientation = other.moveOrientation;
	rotateOrientation = other.rotateOrientation;
	ID = other.ID;
	openingDoor = other.openingDoor;
}


bool ServerPlayer::updateIsAvailable(){
	return updateAvailable;
}

void ServerPlayer::updated(){
	updateAvailable = false;
//	shootingState = SHOOTING_STATE_WAIT;
}


void ServerPlayer::rotate(){
	ang -= PI/36 * rotateOrientation;
	if (ang < 0 || ang >= 2*PI){
		ang += 2*PI*rotateOrientation;
	}
	if (rotateOrientation != ROTATE_QUIET)
		updateAvailable = true;

	dirx = step * cos(ang);
	diry = step * sin(ang);
}

void ServerPlayer::move(){
	position.x += dirx * moveOrientation;
	position.y += diry * moveOrientation;
	if(moveOrientation != MOVE_QUIET)
		updateAvailable = true;

	setDirection(step * cos(ang), step * sin(ang));
}

void ServerPlayer::setDirection(float x, float y){
	dirx = x;
	diry = y;
}

void ServerPlayer::setCurrentWeapon(player_weapons_t aWeapon){
	if(aWeapon < 1 || aWeapon > MAX_WEAPONS)
		return;

	updateAvailable = true;
	currentWP = aWeapon;
	currentWeapon = inventory.getWeapon(currentWeapon, aWeapon);
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
}

void ServerPlayer::stopShooting(){
	shootingState = SHOOTING_STATE_QUIET;
}

weapon_t ServerPlayer::equip(weapon_t weapon){
	weapon_t last;
	updateAvailable = true;
	if ((last = inventory.equip(weapon)) != NONE);
		setCurrentWeapon(WP_SECONDARY);

	return last;
}

//Usa trigonometria para definir la proporcion de daño que le sacara al enemigo
//de acuerdo a la distancia (ad=adyacente) y angulo (op=opuesto)
void ServerPlayer::getDamageCoefficient(ServerPlayer &enemy, float &coef, float wallDist){
	float eX;
	float eY;
	enemy.getPosition(eX, eY);
	Vector enemyPos(eX, eY);
	Vector pos(position.x, position.y);
	float distance = pos.getDistance(enemyPos); 
	float anguloObj = pos.getAngle(enemyPos);
	float difAng = ang - anguloObj;

	if (difAng < -PI){
		difAng += 2*PI;
	}
	if (difAng > PI){
		difAng -= 2*PI;
	}
	if (difAng < 0)
		difAng =- difAng;
	//se forma un triangulo rectangulo con posicion del jugador,
	//direccion de tiro y posicion del enemigo
	float op = sin(difAng) * distance; //cateto opuesto
	float ad = cos(difAng) * distance; //cateto adyacente
	if(ad > wallDist || op > SHOOTING_SIZE){
		coef = 0;
		return;
	}

	float coefDistance = COEF_SHOOTING_DISTANCE_OFFSET + exp(-ad/COEF_SHOOTING_DISTANCE_DIVISOR);
	float coefAng = exp(-op/COEF_SHOOTING_ANGLE_DIVISOR);
	coef = coefDistance * coefAng;
	if(coef > 1)
		coef = 1;
}


int ServerPlayer::shoot(bool &shootMissile){
	int weaponDamage;
	if(ammo < currentWeapon->getBulletsNeeded())
	 	setCurrentWeapon(WP_KNIFE);

	weaponDamage = currentWeapon->shoot(shootingState, shootMissile);
	ammo-=currentWeapon->getUsedBullets();

	return weaponDamage;
}

float ServerPlayer::getDist(ServerPlayer &enemy){
	Vector pPos(position.x, position.y);
	Vector ePos(enemy.position.x, enemy.position.y);

	return pPos.getDistance(ePos) - 2*position.radius;
}

bool ServerPlayer::isDead(){
	return dead;
}

bool ServerPlayer::tryToRespawn(){
	now = std::chrono::high_resolution_clock::now();
	auto wait = std::chrono::duration_cast<std::chrono::milliseconds>(now - timeOfDead);
	if(wait.count() >= TIME_TO_RESPAWN){
		respawn();
		return true;
	}
	return false;
}

void ServerPlayer::respawn(){
	position.x = init_posx;
	position.y = init_posy;
    setCurrentWeapon(WP_KNIFE);
	health = 100;
	ammo = INITIAL_PLAYER_AMMO;
	dead=false;
	inventory.respawn();
}

void ServerPlayer::beDamaged(int damage){
	health -= damage;
	updateAvailable = true;
	if (health <= 0){
		timeOfDead = std::chrono::high_resolution_clock::now();
		dead = true;
		health = 0;
		lifes -= 1;
		updateAvailable = true;
		if (lifes <= 0){
			lifes = 0;
			lost = true;
			// logica muerte
		}			
	}
}


void ServerPlayer::startOpenDoor(){
	openingDoor = true;
}

void ServerPlayer::stopOpenDoor(){
	openingDoor = false;
}

bool ServerPlayer::isOpeningDoor(){
	return openingDoor;
}

size_t ServerPlayer::getID(){
	return ID;
}

float ServerPlayer::getAngle(){
	return ang;
}

int ServerPlayer::heal(int h){
	if (health >= MAX_HEALTH 
	|| (h == HEAL_BLOOD && health > MAX_BLOOD_HEAL_PLAYER))
		return 0;
	updateAvailable = true;

	health = health + h;
	if (health > MAX_HEALTH)
		health = MAX_HEALTH;

	return 1;
}

int ServerPlayer::grabKey(game_key_t k){
	if (k == KEY_BLUE)
		if (blueKey == false){
			blueKey = true;
			return 1;
		}
	if (k == KEY_GOLD)
		if (goldKey == false){
			goldKey = true;
			return 1;
		}
	return 0;
}

int ServerPlayer::addPoints(int p){
	score += p;
	return 1;
}

int ServerPlayer::reload(int a){
	if (ammo >= MAX_AMMO)
		return 0;

	updateAvailable = true;
	ammo += a;
	if (ammo > MAX_AMMO)
		ammo = MAX_AMMO;

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
	p.goldKey = goldKey;
	p.blueKey = blueKey;
	p.dead = dead;
	p.shootingState = shootingState;
	p.ID = ID;
    p.step = step;
	p.lost = lost;
}

player_move_orientation_t ServerPlayer::getMoveOrientation(){
	return moveOrientation;
}

weapon_t ServerPlayer::getSecondaryWPtype(){
	return inventory.getSecondaryWPtype();
}


void ServerPlayer::getPosition(circle &c){
	c.x = position.x;
	c.y = position.y;
	c.radius = position.radius;
}


void ServerPlayer::getPosition(float &x, float &y){
	x = position.x;
	y = position.y;
}

void ServerPlayer::getDirection(float &x, float &y){
	x = dirx;
	y = diry;
}

bool ServerPlayer::isShooting(){
	updateAvailable = true;
	if (shootingState != SHOOTING_STATE_QUIET){
		return true;
	}
	return false;
}

bool ServerPlayer::hasGoldKey(){
	return goldKey;
}

bool ServerPlayer::hasBlueKey(){
	return blueKey;
}

void ServerPlayer::usedGoldKey(){
	goldKey = false;
}

void ServerPlayer::usedBlueKey(){
	blueKey = false;
}
