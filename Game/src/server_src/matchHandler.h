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
    void newMatch(std::string &matchName,
                    int &numberOfPlayers, int &numberOfBots,
                    std::vector<std::vector<int>> &lvls);
    bool addUserToMatch(User *user, std::string matchName);
    void getMatchList(std::stringstream &matchesList);
};

#endif