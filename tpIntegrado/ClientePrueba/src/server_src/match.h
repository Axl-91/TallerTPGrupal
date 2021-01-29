#ifndef MATCH__H
#define MATCH__H

#include <cmath>
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
#include "CollisionMap.h"

class Match : public Thread
{
public:
    // Match();
    Match(std::string matchName);
    ~Match();
    // ~Match();
    void addUser();
    virtual void run() override;
    void operator()();
    void startMatch();
    // void updateUsers();
    void updateGame();
    void addUser(User* user);
    void stop();
    bool isUserNameAvailable(std::string aName);
    std::string getName();
    bool started();
    void delete_finish_clients(std::vector<User*>& threads);
    void readEvents();
    void movePlayer(ServerPlayer &player);
    void handleCollision(circle &playerPos, int c);
    void getPlayerIndex(size_t index);
private:
    ProtectedMatchEventQueue q;
    std::map<size_t, User*> users;
    std::map<size_t, ServerPlayer> players;
    std::atomic<bool> is_running;
    std::atomic<bool> gameStarted;
    std::stringstream game;
    std::string name;
    std::vector<std::vector<int>> lvl1;
    CollisionMap colMap;
    UpdateHandler updateHandler;
    size_t connectionNumber;
    void welcomeUser(User* user);
    
};

#endif