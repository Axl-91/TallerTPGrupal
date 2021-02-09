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
    std::cout << "ServerReceiver.run(): arranco"  << std::endl;
    this->start();
}

void User::setProtectedMatchEventQueue(ProtectedMatchEventQueue *q){
    this->q = q;
}

void User::run(){
    started = true;
    try {
        while(userIsRunning){
            if(receiver.finished()){
                userIsRunning = false;
                continue;
            }
            MatchEvent_t event;
            event_t input;
            readEvent(input);
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
        std::cerr << "Excepcion en User.run():" << std::endl;
    } catch (const std::exception &e){
        std::cerr << "Excepcion en User.run()" << std::endl;
        std::cerr << e.what() << std::endl;
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


void User::readMenuEvent(menu_event_t &menuEvent){
    receiver.readMenuEvent(menuEvent);
}

void User::readEvent(event_t &event){
    receiver.readGameEvent(event);
}
// void User::readInput(std::string &input){
//     receiver.readInput(input);
// }

void User::stop(){
    userIsRunning = false;
}

void User::changeName(std::string &newName){
    userName = newName;
}

void User::sendGameUpdate(update_tag_t &aTag){
    transmitter.sendTag(aTag);
}

void User::sendString(std::string &aString){
    transmitter.sendString(aString);
}
void User::sendMap(std::vector<std::vector<int>> &lvl1){
    transmitter.sendMap(lvl1);
}

std::string User::getName(){
    return userName;
}

void User::sendPlayerInfo(Player_t &p){
    transmitter.sendPlayer(p);
}

void User::update(UpdateHandler &uHandler){
    
    update_tag_t aTag;
    Player_t playerInfo;
    uHandler.getPlayerChange(playerInfo);    

    if(uHandler.mapChangeAvailable()){
        aTag = TAG_MAP_CHANGE;
        Map_change_t aMapChange;
        uHandler.getMapChange(aMapChange);
        sendGameUpdate(aTag);
        transmitter.sendMapUpdate(aMapChange);
    }else{
        aTag = TAG_PLAYER_INFO;
        sendGameUpdate(aTag);
    }
    transmitter.sendPlayer(playerInfo);   

}

void User::setID(size_t newID){
    ID = newID;
}
