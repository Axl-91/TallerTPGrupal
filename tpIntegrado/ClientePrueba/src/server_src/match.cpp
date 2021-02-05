#include "match.h"
#include <algorithm>
// std::vector<std::vector<int>> lvl2 = {
//     {434,434,434,434,434,434,434,434,434},
//     {434,000,000,000,000,000,000,000,434},
//     {434,000,103,434,434,434,434,000,434},
//     {434,000,204,000,000,000,000,000,434},
//     {434,434,434,434,434,401,000,000,434},
//     {434,000,000,000,000,000,000,000,434},
//     {434,000,000,000,000,000,000,000,434},
//     {434,434,434,434,434,434,434,434,434}
// };
// std::vector<std::vector<int>> lvl2 = {
// 	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
// 	{434,000,000,000,000,103,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,435,449,435,435,449,435,435,000,000,000,000,000,103,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,104,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,434,434,434,434,434,000,000,434,434,434,434,000,000,000,000,000,434,434,434},
// 	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,301,301,000,000,000,434},
// 	{434,000,204,204,000,000,000,000,434,434,000,000,000,000,301,301,000,000,000,434},
// 	{434,000,204,204,000,000,000,000,434,434,000,000,000,000,301,301,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
// 	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
// };
std::vector<std::vector<int>> lvl2 = {
	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
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

// void Match::delete_finish_clients(std::vector<User*>& threads){
//     std::vector <MenuHandler*> temp;
//     std::vector <MenuHandler*>::iterator it = threads.begin();
//     for (; it != threads.end() ; ++it){
//         if ((*it)->is_dead()){
//             (*it)->join();
//             delete(*it);
//             *it = NULL;
//         } else {
//             temp.push_back(*it);
//         }
//     }
//     threads.swap(temp);
// }

void Match::readEvents(){
    if(users.size() == 0)
        return;

    // Player_t auxPlayer;
    MatchEvent_t event;

    if(q.isEmpty())
        return;
    event = q.pop();
    std::string command;
    std::stringstream paraEnviar;

    if(event.event == NO_EVENT)
        return;    
    ServerPlayer &aPlayer = players.at(event.playerTag);
    if(event.event==PLAYER_SET_WEAPON_KNIFE){
        aPlayer.setCurrentWeapon(WP_KNIFE);
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
        aPlayer.setMoveOrientation(FORWARD);
    }
    if(event.event==PLAYER_START_MOVING_BACKWARD){
        aPlayer.setMoveOrientation(BACKWARD);
    }
    if(event.event==PLAYER_STOP_MOVING){
        aPlayer.setMoveOrientation(MOVE_QUIET);
    }
    if(event.event==PLAYER_START_ROTATING_RIGHT)
        aPlayer.seteRotateOrientation(RIGHT);
    if(event.event==PLAYER_START_ROTATING_LEFT)
        aPlayer.seteRotateOrientation(LEFT);
    if(event.event==PLAYER_STOP_ROTATING)
        aPlayer.seteRotateOrientation(ROTATE_QUIET);

    if(event.event==GAME_QUIT)
        return;
    if(event.event==PICHIWAR)
        return;
    if(event.event==UNIRME)
        return;

    game.movePlayer(aPlayer);
    aPlayer.rotate();
    updateHandler.updatePlayerPosition(aPlayer);

    if(aPlayer.isShooting()==true){
        std::cout<<"hola match"<<std::endl;
        game.handlePlayerShoot(aPlayer);
    }
    for(auto user:users)
        user.second->update(updateHandler);
}

void Match::stop(){
    is_running = false;
}


void Match::welcomeUser(User* user){
    std::stringstream welcome;
    welcome << "Te uniste a la partida: " << name << std::endl;
    welcome << "Bienvenido!\nPodes chatear con otros jugadores en la sala." << std::endl;
    welcome << "Cantidad de jugadores en la sala: " << users.size() << std::endl;
    user->sendGameUpdate(welcome);


    std::stringstream playerInfo;
    playerInfo << "playerInfo";
    user->sendGameUpdate(playerInfo);
    Player_t auxPlayer;
    players.at(connectionNumber).getPlayerInfo(auxPlayer);
    user->sendPlayerInfo(auxPlayer);
    
    std::stringstream map;
    map << "mapa";
    user->sendGameUpdate(map);
    user->sendMap(lvl1);
}

void Match::addUser(User* user){
    players.emplace(connectionNumber, ServerPlayer(96,96,0, connectionNumber));

    user->setProtectedMatchEventQueue(&q);
    user->setID(connectionNumber);
    users[connectionNumber] = user;
    user->start();

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
