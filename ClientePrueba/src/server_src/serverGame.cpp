#include "serverGame.h"
#include "ShootingRaycaster.h"

ServerGame::ServerGame(std::map<size_t, ServerPlayer> &p,
                        std::vector<std::vector<int>> &l,
						std::queue<UpdateHandler> &q,
					    std::queue<Missile_t> &mUQ):
    players(p),
    lvl1(l),
    colMap(lvl1),
	uQ(q),
	missileUQ(mUQ),
	missileCounter(1)
{}

//
//Genera actualizaciones en el mapa y 
//el jugador de a acuerdo a los cambio en cada evento
void ServerGame::update(){
	Missile_t m;
	//actualizar jugadores
	for (auto &aPlayer: players){
		if(aPlayer.second.isDead()==true)
			aPlayer.second.tryToRespawn();
		else{
		    movePlayer(aPlayer.second);
    		aPlayer.second.rotate();
	    	if (aPlayer.second.isShooting() == true){
        		handlePlayerShoot(aPlayer.second);
    		}
		}

//		if (aPlayer.second.updateIsAvailable() == true){
			updateHandler.updatePlayerPosition(aPlayer.second);
			uQ.emplace(std::move(updateHandler));
			aPlayer.second.updated();
//		}
	}

	updateHandler.updated();

	//actualizar misiles
	for (auto it=missiles.begin(); it!=missiles.cend(); ){
		moveMissile(it->second);
		it->second.getInfo(m);
		missileUQ.push(m);
		//si ya exploto, borralo
		if(it->second.hasExploded()==true)
			missiles.erase(it++);
		else
			it++;			
	}
}

void ServerGame::handlePlayerShoot(ServerPlayer &player){
	float wallDist = shootRaycaster(player);
	float coef=0;
	float damage;
	bool shootMissile;

	damage = player.shoot(shootMissile);
	if(shootMissile ==false){
		for (auto &p: players){
			if (p.first == player.getID())
				continue;
			player.getDamageCoefficient(p.second, coef, wallDist);
			p.second.beDamaged(coef*damage);
		}
	}else{
		addMissile(player, damage);
	}
}

void ServerGame::addMissile(ServerPlayer &player,int damage){
    float x;
	float y;
	float dX;
    float dY;
	float ang;
	size_t ID = missileCounter;
	missileCounter++;
	ang = player.getAngle();
	player.getPosition(x, y);
    player.getDirection(dX, dY);

	ServerMissile m(ID, x+dX*5, y+dY*5, ang, dX, dY, damage);
	missiles.emplace(ID, m);
}

//devuelve la distancia a la pared mas cercana en la direccion del jugador
float ServerGame::shootRaycaster(ServerPlayer &player){
	circle pPosition;
	float pAngle = player.getAngle();
	player.getPosition(pPosition);
	Vector vectorPos(pPosition.x, pPosition.y);
	ShootingRaycaster raycaster(vectorPos, pAngle, colMap);
	float anguloRay = pAngle;
	if (anguloRay < 0){
		anguloRay += 2*PI;
	} else if (anguloRay > 2*PI){
		anguloRay -= 2*PI;
	}

	raycaster.crearRay(anguloRay);
	return raycaster.getDistancia();
}

void ServerGame::moveMissile(ServerMissile &missile){
	float dx;
	float dy;
	circle missilePos;
	int collidableIdentifier;
	missile.getPosition(missilePos);
	missile.getDirection(dx,dy);

	std::vector<Collidable*> col;
	colMap.detectCollision(missilePos, dx, dy, col);
	for (size_t i = 0; i < col.size(); i++){
		if(col[i]->collide(missile)==true){
			missile.explode();
			handleMissileExplosion(missile);
			return;
		}
	}

	if(detectCollisionWithPlayer(missile) == true){
		missile.explode();
		handleMissileExplosion(missile);
		return;
	}

	missile.move();
}

bool ServerGame::detectCollisionWithPlayer(ServerMissile &m){
	for(auto &player: players){
		if(m.detectCollision(player.second) == true)
			return true;
	}
	return false;
}

void ServerGame::handleMissileExplosion(ServerMissile &missile){
	int damage;
	float playerPosX;
	float playerPosY;

	for (auto &p: players){
		p.second.getPosition(playerPosX, playerPosY);
		damage = missile.getExplosionDamage(playerPosX, playerPosY);
		p.second.beDamaged(damage);
	}
	std::cout<<"exploto"<<std::endl;

	return;
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
	dx *= orientation;
	dy *= orientation;

	std::vector<Collidable*> col;
	colMap.detectCollision(playerPos, dx, dy, col);
	for (size_t i = 0; i < col.size(); i++){
		if (col[i]->isInside(playerPos) == false){
			collidableIdentifier = col[i]->collide(player);
			playerPos.x += dx;
			playerPos.y += dy;
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
    if (c >= 400 || c%10 == 0)
		return;

	colMap.erase(playerPos);
    value = 0;
	
	if (c > WEAPON_OFFSET + 2 && c < WEAPON_OFFSET + COLLECTIBLE_OFFSET){
	 	colMap.insert(playerPos.x, playerPos.y, c);
        value = c;
	}
	if (c > 300 && c < 400)
        value = c;
    updateHandler.updateMap(playerPos.x, playerPos.y, value);
}