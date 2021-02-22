#include "matchHandler.h"

MatchHandler::~MatchHandler(){
    for(auto match:matches){
        match.second->stop();
        match.second->join();
        delete(match.second);
    }
}

bool MatchHandler::addUserToMatch(User *user, std::string matchName){

    std::map<std::string, Match*>::iterator it;
	it = matches.find(matchName);
    if (it == matches.end())
		return false;

    // if( !(it->second->isUserNameAvailable(user->getName())) ){
    //     std::stringstream nameNotAvailablemessage;
    //     nameNotAvailablemessage << "El nombre elegido no está disponible en la partida.\n";
    //     user->sendGameUpdate(nameNotAvailablemessage);
    //     return false;
    // }
	it->second->addUser(user);
	return true;
}

void MatchHandler::getMatchList(std::stringstream &matchesList){
    for(auto match:matches){
        matchesList << match.second->getName() << std::endl;
    }
}

void MatchHandler::newMatch(std::string &matchName, std::string &chosenMap,
                    int &numberOfPlayers, int &numberOfBots){
    // checkear que no haya nombre ocupado
    std::cout << "_________ bots:" << numberOfBots << std::endl;
    Match *match = new Match(matchName, chosenMap, numberOfPlayers, 
                            numberOfBots);
    (*match)();
    matches[match->getName()] = match;
}
