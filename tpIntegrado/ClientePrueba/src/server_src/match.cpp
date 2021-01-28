#include "match.h"

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
    lvl1(lvl2)
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

void Match::readEvents(){
    if(users.size() == 0)
        return;
    Player_t auxPlayer;
    event_t event;
    // users[0]->readInput(event);

    if(q.isEmpty())
        return;
    event = q.pop();
    std::string command;
    std::stringstream paraEnviar;
    if(event == NO_EVENT){
        return;    
    }
    
    if(event==PLAYER_SET_WEAPON_KNIFE)
        players[0].setCurrentWeapon(WP_KNIFE);
    if(event==PLAYER_SET_WEAPON_GUN)
        players[0].setCurrentWeapon(WP_GUN);
    if(event==PLAYER_SET_WEAPON_SECONDARY)
        players[0].setCurrentWeapon(WP_SECONDARY);
    if(event==PLAYER_SHOOT)
        players[0].startShooting();
    if(event==PLAYER_STOP_SHOOTING)
        players[0].stopShooting();

    if(event==PLAYER_START_MOVING_FORWARD)
        players[0].setMoveOrientation(FORWARD);
    if(event==PLAYER_START_MOVING_BACKWARD)
        players[0].setMoveOrientation(BACKWARD);

    if(event==PLAYER_STOP_MOVING)
        players[0].setMoveOrientation(MOVE_QUIET);

    if(event==PLAYER_START_ROTATING_RIGHT)
        players[0].seteRotateOrientation(RIGHT);
    if(event==PLAYER_START_ROTATING_LEFT)
        players[0].seteRotateOrientation(LEFT);
    if(event==PLAYER_STOP_ROTATING)
        players[0].seteRotateOrientation(ROTATE_QUIET);

    if(event==GAME_QUIT)
        return;
    if(event==PICHIWAR)
        return;
    if(event==UNIRME)
        return;

    movePlayer(players[0]);
    players[0].rotate();
    updateHandler.updatePlayerPosition(players[0]);
    users[0]->update(updateHandler);
    // for(auto user:users)
    //     user->update(updateHandler);

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
	if(c>102&&c<200){
	 	colMap.insert(playerPos.x, playerPos.y, c);
        value = c;
	}

    updateHandler.updateMap(playerPos.x, playerPos.y, value);
}

void Match::addUser(User* user){
    // user.setID(connectedNumber)
    // connectedNumber++; 
    // Player player 
    // PlayerVector.push_back(player);
    // player.ID = connectedNUmber
    // find TAG, enviar 
    ServerPlayer aPlayer(96,96,0);

    players.push_back(aPlayer);
    user->setProtectedEventQueue(&q);
    users.emplace_back(user);
    user->start();

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
    players[0].getPlayerInfo(auxPlayer);
    users[0]->sendPlayerInfo(auxPlayer);
}

// Envio el contenido de la cola a los clientes
/*
void Match::updateUsers(){
    std::stringstream auxStream;
    while(!q.isEmpty()){
        event_t frase = q.pop();
        if(frase == GAME_QUIT){
            auxStream << "sali";
            for(auto user:users){
                user->sendGameUpdate(auxStream);
            }
        }
        auxStream << frase << std::endl;
    }
    
    for(auto user:users){
        user->sendGameUpdate(auxStream);
    }
}
*/
std::string Match::getName(){
    return name;
}

bool Match::started(){
    return gameStarted;
}

bool Match::isUserNameAvailable(std::string aName){
    for(auto user:users){
        if(user->getName() == aName)
            return false;
    }
    return true;
}
