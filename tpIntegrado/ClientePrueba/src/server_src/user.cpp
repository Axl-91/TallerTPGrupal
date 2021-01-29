#include "user.h"

User::User(Socket socket):
    s(std::move(socket)),
    transmitter(s),
    receiver(s),
    userIsRunning(true),
    started(false),
    userName("randomUser123")
{}

void User::operator()(){
    this->start();
}

void User::setProtectedMatchEventQueue(ProtectedMatchEventQueue *q){
    this->q = q;
}

void User::run(){
    started = true;
    try {
        while(userIsRunning){
            MatchEvent_t event;
            event_t input;
            readInput(input);
            event.event = input;
            event.playerTag = ID;
            if(input == GAME_QUIT){
                q->push(event);
                userIsRunning = false;
                continue;
            }
            q->push(event);
        }
    } catch (const SocketError &e){
        std::cerr << "Excepcion en ServerReceiver.run()" << std::endl;
    } catch (const std::exception &e){
        std::cerr << "Excepcion en User.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

bool User::is_dead(){
    return !userIsRunning;
}
bool User::hasStarted(){
    return started;
}


void User::readInput(event_t &input){
    receiver.readInput(input);
}

// void User::readInput(std::string &input){
//     receiver.readInput(input);
// }

void User::stop(){
    userIsRunning = false;
}

void User::changeName(std::string newName){
    userName = newName;
}

void User::sendGameUpdate(std::stringstream& game){
    transmitter.send(game);
}

void User::sendMap(std::vector<std::vector<int>> &lvl1){
    transmitter.sendMap(lvl1);
}

std::string User::getName(){
    return userName;
}

void User::sendPlayerInfo(Player_t player){
    transmitter.sendPlayer(player);   
}

void User::update(UpdateHandler uHandler){
    
    if(uHandler.mapChangeAvailable()){
        std::stringstream updateMsg;
        updateMsg << "mapChange";
        Map_change_t aMapChange;
        uHandler.getMapChange(aMapChange);
        sendGameUpdate(updateMsg);
        sendMapUpdate(aMapChange);
    }
    if(uHandler.playerChangeAvailable()){
    std::stringstream updateMsg;
        updateMsg << "playerInfo";
        Player_t playerInfo;
        uHandler.getPlayerChange(playerInfo);
        // std::cout << "Usser::update() playerInfo.currentWP: " << playerInfo.currentWP << std::endl;
        // std::cout
        sendGameUpdate(updateMsg);
        sendPlayerInfo(playerInfo);
    }
    uHandler.updated();
}

void User::sendMapUpdate(Map_change_t &aMapChange){
    transmitter.sendMapUpdate(aMapChange);
}

void User::setID(size_t newID){
    ID = newID;
}
