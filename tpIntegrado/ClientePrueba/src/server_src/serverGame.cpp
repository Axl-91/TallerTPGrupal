#include "serverGame.h"

ServerGame::ServerGame(std::map<size_t, ServerPlayer> &p,
                        std::vector<std::vector<int>> &l,
                        UpdateHandler &uH):
    players(p),
    lvl1(l),
    updateHandler(uH),
    colMap(lvl1)
{}


void ServerGame::movePlayer(ServerPlayer &player){
	float dx;
	float dy;
	circle playerPos;
	int collidableIdentifier;
    player_move_orientation_t orientation=player.getMoveOrientation();
	player.getPosition(playerPos);
	player.getDirection(dx,dy);
	dx*=orientation;
	dy*=orientation;

	std::vector<Collidable*> col;
	colMap.detectCollision(playerPos,dx,dy,col);
	for(size_t i=0;i<col.size();i++){
		if(col[i]->isInside(playerPos)==false){
			collidableIdentifier=col[i]->collide(player);
			playerPos.x+=dx;
			playerPos.y+=dy;
			handleCollision(playerPos, collidableIdentifier);
		}
	}
	player.move();
}

void ServerGame::handleCollision(circle &playerPos, int c){
	Collidable *maker;
    int largoBloque = 64;
	int value;
    if(c>=400||c%100==0)
		return;

	colMap.erase(playerPos);
    value=0;
	// mapGame.eraseObj(playerPos.x,playerPos.y);
	if(c>102&&c<200){
	 	colMap.insert(playerPos.x, playerPos.y, c);
        value = c;
		// mapGame.insertWeapon(playerPos.x, playerPos.y, c);
	}

    updateHandler.updateMap(playerPos.x, playerPos.y, value);
}