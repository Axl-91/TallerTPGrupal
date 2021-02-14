#include "matchEventReader.h"

MatchEventReader::MatchEventReader(std::map<size_t, ServerPlayer> &p,
                                ProtectedQueue<MatchEvent_t> &aQueue):
    players(p),
    q(aQueue),
    is_running(false)
{}

void MatchEventReader::run(){
    is_running = true;
    try{
        while(is_running){
            readEvent();
        }
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en MatchEventReader.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

void MatchEventReader::operator()(){
    this->start();
}

void MatchEventReader::stop(){
    is_running = false;
}

bool MatchEventReader::isDead(){
    return !is_running;
}

void MatchEventReader::readEvent(){
    MatchEvent_t event;
    event.event = NO_EVENT;

    q.pop(event);

    if(event.event == NO_EVENT)
        return; 

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

    // if(event.event==GAME_QUIT)
    //     return false;
    // if(event.event==PICHIWAR)
    //     return false;
    // if(event.event==JOIN)
    //     return false;
}