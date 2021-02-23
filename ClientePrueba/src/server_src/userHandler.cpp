#include "userHandler.h"

namespace fs = std::filesystem;

// std::vector<std::vector<int>> lvl2 = {
// 	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,133,000,201,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,133,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,101,102,000,000,000,000,000,000,000,141,142,143,144,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,434,434,350,434,434,434,434,434,434,434,434,434,434,353,434,434,434,434,434},
// 	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,352,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,121,121,434,000,000,000,000,000,000,000,000,121,121,434},
// 	{434,000,113,113,000,000,134,121,434,000,000,113,113,000,000,000,000,135,121,434},
// 	{434,000,113,113,000,000,000,000,434,434,000,113,113,000,000,000,000,000,000,434},
// 	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
// };

// std::vector<std::vector<int>> lvl3 = {
// 	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,141,000,000,201,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,101,102,111,112,113,121,133,134,135,141,142,143,144,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,434,434,434,434,434,000,000,434,434,434,434,000,000,000,000,000,434,434,434},
// 	{434,000,000,000,000,000,000,000,434,434,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
// };

// std::vector<std::vector<int>> lvl4 = {
// 	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,201,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,201,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,201,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,000,101,102,111,112,113,121,133,134,135,141,142,143,144,000,000,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,434,434,434,434,434,000,000,434,434,434,434,000,000,000,434,434,434},
// 	{434,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,000,434},
// 	{434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434,434},
// };
// std::map<std::string, std::vector<std::vector<int>>> lvls = {
//         {"map1",lvl2},
//         {"map2",lvl3},
//         {"map3",lvl4}
// };

UserHandler::UserHandler(User *user, MatchHandler &matches):
    is_running(true),
    matches(matches),
    user(user),
    numberOfPlayers(1),
    numberOfBots(0)
{
    mapMaxPlayers = 1;
    // initializeMaps();
}

UserHandler::~UserHandler(){
    if(user != NULL){
        delete(user);
        user = NULL;
    }
}

// void UserHandler::initializeMaps(){
//     availableMaps.emplace("map1", lvl2);
//     availableMaps.emplace("map2", lvl3);
//     availableMaps.emplace("map3", lvl4);
// }

void UserHandler::operator()(){
    this->start();
}

void UserHandler::run(){
    try{
        while(is_running){
                processInput();
        }
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en userHandler.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

void UserHandler::processInput(){
    menu_event_t event;
    user->readMenuEvent(event);

    if(event.event == NEW_NAME){
        changeUserName(event.info);
    }
    if(event.event == JOIN){
        addUserToMatch(event.info);
    }
    if(event.event == GET_MATCHES){
        sendMatches();
    }
    if(event.event == GET_MAPS){
        sendMaps();
    }
    if(event.event == NEW_MATCH){
        newMatch(event.info);
        addUserToMatch(event.info);
    }
    if(event.event == SET_MAP){
        setChosenMap(event.info);
    }
    if(event.event == SELECT_MAX_PLAYER){
        setMatchMaxPlayers(event.info);
    }
    if(event.event == SELECT_NUMBER_OF_BOTS){
        setNumberOfBots(event.info);
    }
}

void UserHandler::setMatchMaxPlayers(std::string &maxPlayers){
    std::stringstream auxStream(maxPlayers);
    
    auxStream >> numberOfPlayers;
    if(numberOfPlayers > mapMaxPlayers)
        numberOfPlayers = mapMaxPlayers;
}

void UserHandler::setNumberOfBots(std::string &botsNumber){
    std::stringstream auxStream(botsNumber);
    auxStream >> numberOfBots;
}

void UserHandler::setChosenMap(std::string &newName){
    chosenMap = newName;
}

void UserHandler::changeUserName(std::string &newName){
    user->changeName(newName);
}

void UserHandler::newMatch(std::string &matchName){
    initializeMap(chosenMap);
    matches.newMatch(matchName/*, chosenMap*/, numberOfPlayers, numberOfBots,
    map);
    // lvls.at(chosenMap));
}

void UserHandler::addUserToMatch(std::string matchName){
    bool wasAbleToJoin = false;
    wasAbleToJoin = matches.addUserToMatch(user, matchName);
    if(wasAbleToJoin){
        user = NULL;
        stop();
    }
}

void UserHandler::sendMaps(){

    std::cout << "entro a send maps()" << std::endl;
    getDirectoryFiles();
    std::stringstream mapsList;
    for(auto fileName:fileNameVector)
        mapsList << fileName <<std::endl;

    std::cout << mapsList.str() << std::endl;
    // mapsList << "map1
    //             map2
    //             map3";
    // maps.getMapList(mapsList);
    menu_event_t anEvent;
    anEvent.event = GET_MAPS;
    anEvent.info = mapsList.str();
    user->sendString(anEvent.info);
}

void UserHandler::sendMatches(){
    std::stringstream matchesList;
    matches.getMatchList(matchesList);
    menu_event_t anEvent;
    anEvent.event = GET_MATCHES;
    anEvent.info = matchesList.str();
    user->sendString(anEvent.info);
}

bool UserHandler::is_dead(){
    return !is_running;
}

void UserHandler::stop(){
    is_running = false;
}

void UserHandler::initializeMap(std::string &name){
    YAML::Node config = YAML::LoadFile("Media/Maps/" + name + ".yaml");

    mapMaxPlayers = config["players"].as<int>();
	map = config["model"].as<std::vector<std::vector<int>>>();
}

void UserHandler::getDirectoryFiles(){
    std::string path = "Media/Maps";
    for (const auto & entry : fs::directory_iterator(path)){
        std::string file = entry.path().filename().string();
        std::string token = file.substr(0,file.find("."));
        fileNameVector.push_back(token);
    }
}