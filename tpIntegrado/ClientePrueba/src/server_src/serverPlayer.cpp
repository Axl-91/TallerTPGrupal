#include "serverPlayer.h"
#include <iostream>
#include "../common_src/types.h"


#define SHOOTING_ANGLE 0.087263
#define COEF_SHOOTING_DISTANCE_DIVISOR 512
#define COEF_SHOOTING_DISTANCE_OFFSET 0.2
#define SHOOTING_SIZE 20
#define COEF_SHOOTING_ANGLE_DIVISOR 96



ServerPlayer::ServerPlayer(float x, float y, float a, size_t newID):
currentWeapon(inventory.getWeapon(currentWeapon, WP_KNIFE))
{
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
	shooting = false;
	lifes = 3;
	score = 123;
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
    position.x=other.position.x;
    position.y=other.position.y;
    position.radius=16;
    ang=other.ang;
    step=5;
	dirx = other.dirx;
	diry = other.diry;
	currentWP = WP_KNIFE;
	health = 50;
	ammo = 50;
	key = false;
	shooting = false;
	lifes = 3;
	score = 123;
	moveOrientation = MOVE_QUIET;
	rotateOrientation = ROTATE_QUIET;
	ID = other.ID;
}
// void ServerPlayer::setID(size_t newID){
// 	ID = newID;
// }

int toGrados(float radiales){
	float anguloGrados = (radiales / PI) * 180;
	int anguloInt = round(anguloGrados);
	return anguloInt;
}

bool ServerPlayer::updateIsAvailable(){
	return updateAvailable;
}

void ServerPlayer::updated(){
	updateAvailable=false;
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
	shooting = true;
}

void ServerPlayer::stopShooting(){
	shooting = false;
}

weapon_t ServerPlayer::equip(weapon_t weapon){
	weapon_t last;
	updateAvailable=true;
	if((last=inventory.equip(weapon))!=NONE);
		setCurrentWeapon(WP_SECONDARY);

	return last;
}



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
	float coefDistance= COEF_SHOOTING_DISTANCE_OFFSET+exp(-ad/COEF_SHOOTING_DISTANCE_DIVISOR);
	float coefAng= exp(-op/COEF_SHOOTING_ANGLE_DIVISOR);
	coef=coefDistance*coefAng;
	if(coef>1)
		coef=1;

}

// void ServerPlayer::shoot(){
// 	currentWeapon->shoot();
// }

void ServerPlayer::shoot(ServerPlayer &enemy, float coef){
	float weaponDamage;
	int totalDamage;
	std::cout<<"DISPARO!! "<<std::endl;
	std::cout<<"tipo de arma: "<<currentWeapon->getType()<<std::endl;
	weaponDamage = currentWeapon->shoot(this->getDist(enemy), shooting);
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
	if(health<=0)
		//MORIR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
		health=0;
	std::cout<<"vida: "<<health<<std::endl;
}

bool ServerPlayer::isShooting(){
	if(shooting == true)
		updateAvailable=true;

	return shooting;
}

size_t ServerPlayer::getID(){
	return ID;
}

float ServerPlayer::getAngle(){
	return ang;
}

int ServerPlayer::heal(int h){
	if(health>=MAX_HEALTH)
		return 0;
	std::cout<<"health before: "<<health<<std::endl;
	updateAvailable=true;

	health=health+h;
	if(health>MAX_HEALTH)
		health=MAX_HEALTH;
	std::cout<<"health after: "<<health<<std::endl;

	// hudGame.setHealth(health);
	return 1;
}

int ServerPlayer::reload(int a){
	if(ammo>=MAX_AMMO)
		return 0;

	updateAvailable=true;
	std::cout<<"ammo before: "<<ammo<<std::endl;
	ammo+=a;
	if(ammo>MAX_AMMO)
		ammo=MAX_AMMO;
	std::cout<<"ammo after: "<<ammo<<std::endl;

	return 1;
}
void ServerPlayer::getPlayerInfo(Player_t &p){
    p.x = position.x;
    p.y = position.y;
    p.ang = ang;
    p.dirx = dirx;
    p.diry = diry;
	// p.currentWP = currentWP;
	// p.secondaryWP = secondaryWP;
	p.currentWP = currentWP;
	p.secondaryWP = getSecondaryWPtype();

	p.ammo = ammo;
	p.health = health;
	p.lifes = lifes;
	p.score = score;
	p.key = key;
	p.shooting = shooting;
	p.ID = ID;
    // p.step = step;
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