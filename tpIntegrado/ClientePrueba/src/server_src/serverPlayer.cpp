#include "serverPlayer.h"
#include <iostream>
#include "../common_src/types.h"

ServerPlayer::ServerPlayer(float x, float y, float a, size_t newID){
    position.x=x;
    position.y=y;
    position.radius=16;
    ang=a;
    step=5;
	dirx = step*cos(ang);
	diry = step*sin(ang); 
	secondaryWP = NONE;
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
}
ServerPlayer::~ServerPlayer(){}

// void ServerPlayer::setID(size_t newID){
// 	ID = newID;
// }

int toGrados(float radiales){
	float anguloGrados = (radiales / PI) * 180;
	int anguloInt = round(anguloGrados);
	return anguloInt;
}

void ServerPlayer::rotate(){
	ang -= PI/36*rotateOrientation;
	if (toGrados(ang) < 0){
		ang += 2*PI*rotateOrientation;
	}
	dirx = step*cos(ang);
	diry = step*sin(ang);
}

void ServerPlayer::move(){
	position.x+=dirx*moveOrientation;
	position.y+=diry*moveOrientation;
	setDirection(step*cos(ang), step*sin(ang));
}

void ServerPlayer::setDirection(float x, float y){
	dirx=x;
	diry=y;
}

void ServerPlayer::setCurrentWeapon(player_weapons_t aWeapon){
	if((aWeapon == WP_SECONDARY) && (secondaryWP == NONE))
		return;
	currentWP = aWeapon;
}

void ServerPlayer::setMoveOrientation(player_move_orientation_t o){
	moveOrientation = o;
}
void ServerPlayer::seteRotateOrientation(player_rotate_orientation_t o){
	rotateOrientation = o;
}

void ServerPlayer::startShooting(){
	shooting = true;
}

void ServerPlayer::stopShooting(){
	shooting = false;
}

weapon_t ServerPlayer::equip(weapon_t weapon){
    weapon_t last;
	// std::cout << "SVPlayer::equipo() weapon: " << weapon << std::endl;
	
	if(secondaryWP == NONE){
		secondaryWP = weapon;	
		currentWP = WP_SECONDARY;
		return GUN;
	}
	if(secondaryWP == weapon){
		currentWP = WP_SECONDARY;
		return NONE;
	}
	last=secondaryWP;
	secondaryWP = weapon;
	currentWP = WP_SECONDARY;
	return last;
}

int ServerPlayer::heal(int h){
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

int ServerPlayer::reload(int a){
	if(ammo>=MAX_AMMO)
		return 0;

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
	p.currentWP = currentWP;
	p.secondaryWP = secondaryWP;
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