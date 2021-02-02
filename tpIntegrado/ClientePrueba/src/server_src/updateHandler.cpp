#include "updateHandler.h"
#include <iostream>
void UpdateHandler::updatePlayerPosition(ServerPlayer &p){
    playerChanged = true;
    p.getPlayerInfo(player);
}

void UpdateHandler::updateMap(int xAux, int yAux, int value){
    mapChanged = true;
    mapChange.x = xAux;
    mapChange.y = yAux;
    mapChange.value = value;
    mapChange.changeAvailable = true;
}

bool UpdateHandler::mapChangeAvailable(){
    return mapChanged;
}
bool UpdateHandler::playerChangeAvailable(){
    return playerChanged;
}

void UpdateHandler::getMapChange(Map_change_t &aMapChange){
    aMapChange.x =mapChange.x;
    aMapChange.y = mapChange.y;
    aMapChange.value = mapChange.value;
    aMapChange.changeAvailable = mapChange.changeAvailable;

}

void UpdateHandler::getPlayerChange(Player_t &p){
    p.ID = player.ID;
    p.x = player.x;
    p.y = player.y;
    p.ang = player.ang;
    p.dirx = player.dirx;
    p.diry = player.diry;
    // std::cout << "UpdateHandler. getPlayerupdate() currentWP: " << player.currentWP << std::endl;
	p.currentWP = player.currentWP;
	p.secondaryWP = player.secondaryWP;
	p.ammo = player.ammo;
	p.key = player.key;
	p.shooting = player.shooting;
    p.lifes = player.lifes;
    p.score = player.score;
    p.health = player.health;
}

void UpdateHandler::updated(){
    mapChanged = false;
    // playerChanged = false;
}