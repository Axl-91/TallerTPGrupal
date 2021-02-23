#ifndef MATCH__H
#define MATCH__H

#include <sstream>
#include <vector>
#include <atomic>
#include <map>
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "user.h"
#include "../common_src/protectedEventQueue.h"
#include "protectedMatchEventQueue.h"
#include "../common_src/types.h"
#include "serverPlayer.h"
#include "serverGame.h"
#include "matchEventReader.h"
#include "bot.h"
struct initPos{
    int x;
    int y;
};


class Match : public Thread
{
public:
    Match(std::string &matchName,// std::string &chosenMap,
                    int &numberOfPlayers, int &numberOfBots,
                    std::vector<std::vector<int>> &lvls);
    ~Match();
    void addUser();
    virtual void run() override;
    void operator()();
    void startMatch();
    void updateUsers();

    void addUser(User* user);
    void stop();
    bool isUserNameAvailable(std::string aName);
    std::string getName();
    bool started();
    void delete_finish_clients(std::vector<User*>& threads);
    void getPlayerIndex(size_t index);

private:
    int playersOnMap;
    std::map<size_t, initPos> initPositions;
    ProtectedQueue<MatchEvent_t> q;
    std::map<size_t, User*> users;
    std::map<size_t, ServerPlayer> players;
    std::atomic<bool> is_running;
    std::atomic<bool> gameStarted;
    std::string name;
    std::vector<std::vector<int>> lvl1;
    UpdateHandler updateHandler;
    std::queue<UpdateHandler> uQ; 
    std::queue<Missile_t> missileUQ; 

    size_t connectionNumber;
    ServerGame game;
    
    void initializeInitPosition(std::vector<std::vector<int>> &map);
    void initializeMaps();
    void welcomeUser(User* user);

    std::map<size_t, Bot*> bots;
    // Bot bot;
    MatchEventReader matchEventReader;
};

#endif