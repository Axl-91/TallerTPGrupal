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
}

void UpdateHandler::getPlayerChange(Player_t &p){
    p = player;
}

void UpdateHandler::updated(){
    mapChanged = false;
    // playerChanged = false;
}