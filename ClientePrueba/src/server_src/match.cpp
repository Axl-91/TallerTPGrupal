#include "match.h"
#include <algorithm>
#include <chrono>

std::vector<std::vector<int>> lvl2 = {
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,201,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,101,102,111,112,113,121,133,134,135,141,142,143,144,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,000,000,434,434,434,434,000,000,000,000,000,434,434,434},
	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
};

std::vector<std::vector<int>> lvl3 = {
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,141,000,000,201,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,101,102,111,112,113,121,133,134,135,141,142,143,144,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,000,000,434,434,434,434,000,000,000,000,000,434,434,434},
	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
};

std::vector<std::vector<int>> lvl4 = {
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
	{434,000,000,000,000,000,000,000,000,000,000,201,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,201,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,201,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,101,102,111,112,113,121,133,134,135,141,142,143,144,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,000,000,434,434,434,434,000,000,000,434,434,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
};
std::map<std::string, std::vector<std::vector<int>>> lvls = {
        {"map1",lvl2},
        {"map2",lvl3},
        {"map3",lvl4}
};
Match::Match(std::string &matchName, std::string &chosenMap):
    is_running(true),
    name(matchName),
    lvl1(lvls.at(chosenMap)),
    connectionNumber(0),
    game(players, lvl1, uQ)
{
    initializeInitPosition();
    initializeMaps();
    // lvl1 = availableMaps.at(chosenMap);
}

void Match::initializeMaps(){
    availableMaps.emplace("map1", lvl2);
    availableMaps.emplace("map2", lvl3);
    availableMaps.emplace("map3", lvl4);
}

void Match::initializeInitPosition(){
    initPos aux0;
    aux0.x = 96;
    aux0.y = 96;
    initPos aux1;
    aux1.x = 196;
    aux1.y = 196;
    initPos aux2;
    aux2.x = 296;
    aux2.y = 296;
    initPos aux3;
    aux3.x = 396;
    aux3.y = 396;
    initPositions.emplace(0, aux0);
    initPositions.emplace(1, aux1);
    initPositions.emplace(2, aux2);
    initPositions.emplace(3, aux3);
}

Match::~Match(){
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
    long timeStep= 40;
    try{
        while(is_running){
            auto initial = std::chrono::high_resolution_clock::now();
            readEvents();
            game.update();
            updateUsers();

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
    if(event.event==JOIN)
        return false;

    return true;
}


void Match::updateUsers(){
    while (uQ.empty()==false){
        for(auto user:users)
            user.second->update(uQ.front());
        uQ.pop();
    }
}

void Match::stop(){
    is_running = false;
}

// Le manda al usuario su información inicial
void Match::welcomeUser(User* user){
    update_tag_t aTag = TAG_PLAYER_INFO;
    user->sendGameUpdate(aTag);

    Player_t auxPlayer;
    players.at(connectionNumber).getPlayerInfo(auxPlayer);
    user->sendPlayerInfo(auxPlayer);

    aTag = TAG_MAP_INIT;    
    user->sendGameUpdate(aTag);
    user->sendMap(lvl1);
}

// Carga al usuario y sus atributos iniciales al contenedor
void Match::addUser(User* user){
    initPos auxPos;
    auxPos = initPositions.at(connectionNumber % 4);

    ServerPlayer auxPlayer(auxPos.x, auxPos.y, 0, connectionNumber);
    players.emplace(connectionNumber, std::move(auxPlayer));
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
