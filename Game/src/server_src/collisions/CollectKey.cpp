#include "CollectKey.h"


CollectKey::CollectKey(int xI, int yI, int cellWidth, int k):
Collectible(xI, yI, cellWidth){
    type=(game_key_t) k;
}

int CollectKey::collide(ServerPlayer &p){
    return (int)p.grabKey(type)+KEY_OFFSET;
}

CollectKey::~CollectKey(){}

