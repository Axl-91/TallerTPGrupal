#ifndef MENUHANDLER__T
#define MENUHANDLER__T

#include <vector>
#include <algorithm>
#include <map>
#include "../common_src/thread.h"
#include "match.h"
#include "user.h"
#include "matchHandler.h"

class MenuHandler : public Thread {
public:
    MenuHandler(User *user, MatchHandler &matches);
    ~MenuHandler();
    virtual void run() override;
    void operator()();
    void sendMatches();
    void processInput();
    bool isMatchAvailable(size_t i);
    void stop();
    bool is_dead();
    void addUserToMatch(std::string matchName);
    void newMatch();
    void joinMatch();
    void changeUserName();
private:
    std::atomic<bool> is_running;
    MatchHandler &matches;
    User* user;
};

#endif
