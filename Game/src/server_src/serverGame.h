#ifndef SERVERGAME__T
#define SERVERGAME__T

#include <map>
#include <vector>
#include <cmath>
#include "../common_src/types.h"
#include "serverPlayer.h"
#include "CollisionMap.h"
#include "updateHandler.h"
#include "ServerMissile.h"

//
//Clase que se ocupa de la logica del juego
class ServerGame{
private:
    std::map<size_t, ServerPlayer> &players;
    std::map<size_t, ServerMissile> missiles;
    int missileCounter;

    std::vector<std::vector<int>> &lvl1;
    UpdateHandler updateHandler;
    CollisionMap colMap;
    std::queue<UpdateHandler> &uQ; 
    std::queue<Missile_t> &missileUQ; 

public:
    ServerGame(std::map<size_t, ServerPlayer> &p,
                std::vector<std::vector<int>> &l,
                std::queue<UpdateHandler> &q,
                std::queue<Missile_t> &mUQ);
    // ~ServerGame();
    float shootRaycaster(ServerPlayer &player);
    bool detectCollisionWithPlayer(ServerMissile &m);

    void addMissile(ServerPlayer &player,int damage);
    void moveMissile(ServerMissile &missille);
    void handleMissileExplosion(ServerMissile &missile);

    void update();
    void updateMissiles();
    void updatePlayers();

    void movePlayer(ServerPlayer &player);
    void handlePlayerShoot(ServerPlayer &player);

    void handleCollision(circle &playerPos, int c);
};

#endif 
