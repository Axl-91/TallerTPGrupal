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
    Match(std::string &matchName, std::string &chosenMap);
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
    // bool readEvents();
    void getPlayerIndex(size_t index);

private:
    std::map<size_t, initPos> initPositions;
    // ProtectedMatchEventQueue q;
    ProtectedQueue<MatchEvent_t> q;
    std::map<size_t, User*> users;
    std::map<size_t, ServerPlayer> players;
    std::map<std::string, std::vector<std::vector<int>>> availableMaps;
    std::atomic<bool> is_running;
    std::atomic<bool> gameStarted;
    // std::stringstream game;
    std::string name;
    std::vector<std::vector<int>> lvl1;
    UpdateHandler updateHandler;
    std::queue<UpdateHandler> uQ; 
    size_t connectionNumber;
    ServerGame game;
    void initializeInitPosition();
    void initializeMaps();
    void welcomeUser(User* user);
    Bot bot;
    MatchEventReader matchEventReader;
};

#endif