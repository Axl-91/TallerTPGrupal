#include "match.h"
#include <algorithm>
// std::vector<std::vector<int>> lvl2 = {
//     {434,434,434,434,434,434,434,434,434},
//     {434,000,104,000,000,000,000,000,434},
//     {434,000,103,434,434,434,434,000,434},
//     {434,000,000,000,000,000,000,000,434},
//     {434,434,434,434,434,401,103,000,434},
//     {434,000,000,000,000,000,000,000,434},
//     {434,000,000,000,000,000,000,000,434},
//     {434,434,434,434,434,434,434,434,434}
// };
std::vector<std::vector<int>> lvl2 = {
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
	{434,000,000,000,000,103,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,435,449,435,435,449,435,435,000,000,000,000,000,103,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,104,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,000,000,434,434,434,434,000,000,000,000,000,434,434,434},
	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,301,301,000,000,000,434},
	{434,000,204,204,000,000,000,000,434,434,000,000,000,000,301,301,000,000,000,434},
	{434,000,204,204,000,000,000,000,434,434,000,000,000,000,301,301,000,000,000,434},
	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
};

Match::Match(std::string matchName):
    is_running(true),
    name(matchName),
    colMap(lvl2),
    lvl1(lvl2),
    connectionNumber(0)
{}

Match::~Match(){
    for (size_t i = 0; i < users.size(); i++){
        if(users.at(i)->hasStarted()){
            users.at(i)->stop();
            users.at(i)->join();    
        }
        delete(users.at(i));
    }
}

void Match::operator()(){
    this->start();
}

void Match::run(){
    try{
        while(is_running){
            readEvents();
            // updateUsers();
    		sleep(1/60);

        }
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en Match.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

// void Match::getPlayerIndex(size_t index){
//     std::vector<ServerPlayer>::iterator it = std::find(players.begin(), players.end(), );
//     if (it != players.end())
//         index = std::distance(players.begin(), it);
// }

void Match::readEvents(){
    if(users.size() == 0)
        return;
    Player_t auxPlayer;
    MatchEvent_t event;
    // users[0]->readInput(event);

    if(q.isEmpty())
        return;
    event = q.pop();
    std::string command;
    std::stringstream paraEnviar;
    if(event.event == NO_EVENT){
        return;    
    }
        std::cout <<"el tag usado es: " << event.playerTag << std::endl;
    
    // size_t i;
    // getPlayerIndex(i);
    ServerPlayer &aPlayer = players.at(event.playerTag);
    if(event.event==PLAYER_SET_WEAPON_KNIFE){
        aPlayer.setCurrentWeapon(WP_KNIFE);
        // players[event.playerTag].setCurrentWeapon(WP_KNIFE);
        // players[event.playerTag].setCurrentWeapon(WP_KNIFE);
    }
    if(event.event==PLAYER_SET_WEAPON_GUN){
        aPlayer.setCurrentWeapon(WP_GUN);
    }
    if(event.event==PLAYER_SET_WEAPON_SECONDARY){
        aPlayer.setCurrentWeapon(WP_SECONDARY);
    }
    if(event.event==PLAYER_SHOOT)
        aPlayer.startShooting();
    if(event.event==PLAYER_STOP_SHOOTING)
        aPlayer.stopShooting();

    if(event.event==PLAYER_START_MOVING_FORWARD){
        // movePlayer(FORWARD, players[0]);
        aPlayer.setMoveOrientation(FORWARD);
    }
    if(event.event==PLAYER_START_MOVING_BACKWARD){
        aPlayer.setMoveOrientation(BACKWARD);
    //     movePlayer(BACKWARD, players[0]);
    }
    if(event.event==PLAYER_STOP_MOVING){
        aPlayer.setMoveOrientation(MOVE_QUIET);
    //     movePlayer(BACKWARD, players[0]);
    }

    if(event.event==PLAYER_START_ROTATING_RIGHT)
        aPlayer.seteRotateOrientation(RIGHT);
        // players[0].rotatePlayerRight();
    if(event.event==PLAYER_START_ROTATING_LEFT)
        aPlayer.seteRotateOrientation(LEFT);
        // players[0].rotatePlayerLeft();
    if(event.event==PLAYER_STOP_ROTATING)
        aPlayer.seteRotateOrientation(ROTATE_QUIET);

    if(event.event==GAME_QUIT)
        return;
    if(event.event==PICHIWAR)
        return;
    if(event.event==UNIRME)
        return;

    movePlayer(aPlayer);
    aPlayer.rotate();

    updateHandler.updatePlayerPosition(aPlayer);
    // for (auto user:users)
    //     user.second->update(updateHandler);
    users.at(event.playerTag)->update(updateHandler);
}

void Match::stop(){
    is_running = false;
}
void Match::movePlayer(ServerPlayer &player){
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

void Match::handleCollision(circle &playerPos, int c){
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

void Match::welcomeUser(User* user){
    std::stringstream welcome;
    welcome << "Te uniste a la partida: " << name << std::endl;
    welcome << "Bienvenido!\nPodes chatear con otros jugadores en la sala." << std::endl;
    welcome << "Cantidad de jugadores en la sala: " << users.size() << std::endl;
    user->sendGameUpdate(welcome);

    std::stringstream map;
    map << "mapa";
    user->sendGameUpdate(map);
    user->sendMap(lvl1);

    std::stringstream playerInfo;
    playerInfo << "playerInfo";
    user->sendGameUpdate(playerInfo);
    Player_t auxPlayer;
    players.at(connectionNumber).getPlayerInfo(auxPlayer);
    user->sendPlayerInfo(auxPlayer);
}

void Match::addUser(User* user){
    // ServerPlayer aPlayer(96,96,0);

    std::cout <<"tag que asigno es:"<< connectionNumber << std::endl;
    
    players.emplace(connectionNumber, ServerPlayer(96,96,0));
    // players[connectionNumber] = std::move(aPlayer);

        std::cout <<"guarde player en mapa" << std::endl;

    user->setProtectedMatchEventQueue(&q);
    user->setID(connectionNumber);
    users[connectionNumber] = user;
    user->start();
        std::cout <<"guarde user en mapa" << std::endl;

    welcomeUser(user);
    connectionNumber++;
}

std::string Match::getName(){
    return name;
}

bool Match::started(){
    return gameStarted;
}

bool Match::isUserNameAvailable(std::string aName){
    for(auto user:users){
        if(user.second->getName() == aName)
            return false;
    }
    return true;
}
