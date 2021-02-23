#ifndef USERHANDLER__T
#define USERHANDLER__T

#include "yaml-cpp/yaml.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <map>
#include "../common_src/thread.h"
#include "match.h"
#include "user.h"
#include "matchHandler.h"

class UserHandler : public Thread {
public:
    UserHandler(User *user, MatchHandler &matches);
    ~UserHandler();
    virtual void run() override;
    void operator()();
    void stop();
    bool is_dead();
private:
    std::atomic<bool> is_running;
    MatchHandler &matches;
    User* user;
    std::string chosenMap;
    std::string chosenMatch;
    int numberOfPlayers;
    int numberOfBots;
    std::map<std::string, std::vector<std::vector<int>>> availableMaps;
    void sendMatches();
    void sendMaps();
    bool isMatchAvailable(size_t i);
    void processInput();
    void setMatchMaxPlayers(std::string &maxPlayers);
    void addUserToMatch(std::string matchName);
    void newMatch(std::string &newMatch);
    void joinMatch(std::string &newName);
    void changeUserName(std::string &newName);
    void setChosenMap(std::string &newName);
    void setNumberOfBots(std::string &newName);
    // void initializeMaps();
    void initializeMap(std::string &name);
    void getDirectoryFiles();
    std::vector<std::string> fileNameVector;
    std::vector<std::vector<int>> map;
    int mapMaxPlayers;
};

#endif
