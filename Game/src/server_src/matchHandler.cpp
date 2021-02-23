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

	it->second->addUser(user);
	return true;
}

void MatchHandler::getMatchList(std::stringstream &matchesList){
    for(auto match:matches){
        matchesList << match.second->getName() << std::endl;
    }
}

void MatchHandler::newMatch(std::string &matchName, //std::string &chosenMap,
                    int &numberOfPlayers, int &numberOfBots,
                    std::vector<std::vector<int>> &lvls){
    // checkear que no haya nombre ocupado
    Match *match = new Match(matchName, numberOfPlayers, 
                            numberOfBots, lvls);
    (*match)();
    matches[match->getName()] = match;
}
