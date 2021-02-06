#include "match.h"
#include <algorithm>
#include <chrono>

std::vector<std::vector<int>> lvl2 = {
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,103,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,104,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,000,000,434,434,434,434,000,000,000,000,000,434,434,434},
	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
};

Match::Match(std::string matchName):
    is_running(true),
    name(matchName),
    lvl1(lvl2),
    connectionNumber(0),
    game(players, lvl1, updateHandler)
{}

Match::~Match(){
    // for (size_t i = 0; i < users.size(); i++){
    for (auto user:users){
        if(user.second->hasStarted()){
            user.second->stop();
            user.second->join();    
        }
        delete(user.second);
    }
}

void Match::operator()(){
    this->start();
}

void Match::run(){
    long timeStep= 30;
    try{
        while(is_running){
            auto initial = std::chrono::high_resolution_clock::now();
            // if(readEvents()==true){
            readEvents();

                game.update();
                updateUsers();
            // }
    		// sleep(30/60);
            auto final = std::chrono::high_resolution_clock::now();
            auto loopDuration = std::chrono::duration_cast<std::chrono::milliseconds>(final - initial);
            long sleepTime = timeStep - loopDuration.count();
            if (sleepTime > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
        }
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en Match.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

bool Match::readEvents(){
    if(users.size() == 0)
        return false;

    // Player_t auxPlayer;
    MatchEvent_t event;

    if(q.isEmpty())
        return false;

    event = q.pop();
    std::string command;
    std::stringstream paraEnviar;

    if(event.event == NO_EVENT)
        return false;    

    ServerPlayer &aPlayer = players.at(event.playerTag);
    if(event.event==PLAYER_SET_WEAPON_KNIFE)
        aPlayer.setCurrentWeapon(WP_KNIFE);
    if(event.event==PLAYER_SET_WEAPON_GUN)
        aPlayer.setCurrentWeapon(WP_GUN);
    if(event.event==PLAYER_SET_WEAPON_SECONDARY)
        aPlayer.setCurrentWeapon(WP_SECONDARY);
    if(event.event==PLAYER_SHOOT)
        aPlayer.startShooting();
    if(event.event==PLAYER_STOP_SHOOTING)
        aPlayer.stopShooting();
    if(event.event==PLAYER_START_MOVING_FORWARD)
        aPlayer.setMoveOrientation(FORWARD);
    if(event.event==PLAYER_START_MOVING_BACKWARD)
        aPlayer.setMoveOrientation(BACKWARD);
    if(event.event==PLAYER_STOP_MOVING)
        aPlayer.setMoveOrientation(MOVE_QUIET);
    if(event.event==PLAYER_START_ROTATING_RIGHT)
        aPlayer.seteRotateOrientation(RIGHT);
    if(event.event==PLAYER_START_ROTATING_LEFT)
        aPlayer.seteRotateOrientation(LEFT);
    if(event.event==PLAYER_STOP_ROTATING)
        aPlayer.seteRotateOrientation(ROTATE_QUIET);

    if(event.event==GAME_QUIT)
        return false;
    if(event.event==PICHIWAR)
        return false;
    if(event.event==UNIRME)
        return false;

    // game.movePlayer(aPlayer);
    // aPlayer.rotate();
    // updateHandler.updatePlayerPosition(aPlayer);

    // if(aPlayer.isShooting()==true){
    //     game.handlePlayerShoot(aPlayer);
    // }
    // for(auto user:users)
    //     user.second->update(updateHandler);

    // updateHandler.updated();
    return true;
}


void Match::updateUsers(){
    for(auto user:users)
        user.second->update(updateHandler);

    updateHandler.updated();
}

void Match::stop(){
    is_running = false;
}


void Match::welcomeUser(User* user){
    std::stringstream welcome;
    welcome << "Te uniste a la partida: " << name << std::endl;
    welcome << "Bienvenido!\nPodes chatear con otros jugadores en la sala." << std::endl;
    welcome << "Cantidad de jugadores en la sala: " << users.size() << std::endl;
    // user->sendText(welcome);
    update_tag_t aTag = TAG_PLAYER_INFO;
    user->sendGameUpdate(aTag);

    Player_t auxPlayer;
    players.at(connectionNumber).getPlayerInfo(auxPlayer);
    user->sendPlayerInfo(auxPlayer);

    aTag = TAG_MAP_INIT;    
    user->sendGameUpdate(aTag);
    user->sendMap(lvl1);
}

void Match::addUser(User* user){
    ServerPlayer aux(96, 96, 0, connectionNumber);
    players.emplace(connectionNumber, std::move(aux));
    user->setProtectedMatchEventQueue(&q);
    user->setID(connectionNumber);
    users[connectionNumber] = user;

    user->start();

    welcomeUser(user);
    std::cout << "se guardo el ID: "  << connectionNumber << std::endl;
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
