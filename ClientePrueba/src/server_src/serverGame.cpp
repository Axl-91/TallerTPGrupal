#include "serverGame.h"
#include "ShootingRaycaster.h"

ServerGame::ServerGame(std::map<size_t, ServerPlayer> &p,
                        std::vector<std::vector<int>> &l,
                        UpdateHandler &uH,
						std::queue<UpdateHandler> &q):
    players(p),
    lvl1(l),
    updateHandler(uH),
    colMap(lvl1),
	uQ(q)
{}


void ServerGame::update(){
	for(auto &aPlayer: players){
	    movePlayer(aPlayer.second);
    	aPlayer.second.rotate();
	    if(aPlayer.second.isShooting()==true){
        	handlePlayerShoot(aPlayer.second);
    	}
		if(aPlayer.second.updateIsAvailable()==true){
			updateHandler.updatePlayerPosition(aPlayer.second);
			uQ.emplace(std::move(updateHandler));
			aPlayer.second.updated();
		}
	}
}

void ServerGame::handlePlayerShoot(ServerPlayer &player){
	float wallDist=shootRaycaster(player);
	float coef;
	for(auto &p: players){
		if(p.first==player.getID())
			continue;

		player.getDamageCoefficient(p.second, coef, wallDist);

		// if(coef!=0)
		player.shoot(p.second, coef);
	}
}



float ServerGame::shootRaycaster(ServerPlayer &player){
	circle pPosition;
	float pAngle=player.getAngle();
	player.getPosition(pPosition);
	Vector vectorPos(pPosition.x, pPosition.y);
	ShootingRaycaster raycaster(vectorPos, pAngle, colMap);
	float anguloRay = pAngle;
	if (anguloRay < 0){
		anguloRay += 2*PI;
	} else if (anguloRay > 2*PI){
		anguloRay -=2*PI;
	}

	raycaster.crearRay(anguloRay);
	return raycaster.getDistancia();
}



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
    if(c>=400||c%10==0)
		return;

	colMap.erase(playerPos);
    value=0;
	// mapGame.eraseObj(playerPos.x,playerPos.y);
	if(c>130&&c<140){
	 	colMap.insert(playerPos.x, playerPos.y, c);
        value = c;
		// mapGame.insertWeapon(playerPos.x, playerPos.y, c);
	}

    updateHandler.updateMap(playerPos.x, playerPos.y, value);
}