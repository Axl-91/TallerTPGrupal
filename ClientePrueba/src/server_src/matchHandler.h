#ifndef MATCHHANDLER__T
#define MATCHHANDLER__T

#include <map>
#include <string>
#include <sstream>
#include "match.h"

class MatchHandler{
private:
    std::map<std::string, Match*> matches;
public:
    ~MatchHandler();
    // virtual void run() override;
    // void operator()();
    void newMatch(std::string &matchName, std::string &chosenMap,
                    int &numberOfPlayers, int &numberOfBots);
    // bool isMatchAvailable(size_t i);
    bool addUserToMatch(User *user, std::string matchName);
    void getMatchList(std::stringstream &matchesList);
};

#endif