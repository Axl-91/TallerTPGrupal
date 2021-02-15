#include "serverGame.h"
#include "ShootingRaycaster.h"

ServerGame::ServerGame(std::map<size_t, ServerPlayer> &p,
                        std::vector<std::vector<int>> &l,
						std::queue<UpdateHandler> &q):
    players(p),
    lvl1(l),
    colMap(lvl1),
	uQ(q)
{}

//
//Genera actualizaciones en el mapa y 
//el jugador de a acuerdo a los cambio en cada evento
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
	float coef=0;

	for(auto &p: players){
		if(p.first==player.getID())
			continue;

		player.getDamageCoefficient(p.second, coef, wallDist);
		player.shoot(p.second, coef);
	}
}


//devuelve la distancia a la pared mas cercana en la direccion del jugador
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


//evalua posible colisiones en la posicion siguiente del jugador
//maneja las colisiones
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

//actualiza el mapa de acuerdo a la colision del jugador
void ServerGame::handleCollision(circle &playerPos, int c){
	Collidable *maker;
    int largoBloque = 64;
	int value;
    if(c>=400||c%10==0)
		return;

	colMap.erase(playerPos);
    value=0;
	if(c>130&&c<140){
	 	colMap.insert(playerPos.x, playerPos.y, c);
        value = c;
	}
    updateHandler.updateMap(playerPos.x, playerPos.y, value);
}