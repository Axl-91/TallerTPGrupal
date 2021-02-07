#ifndef MENUHANDLER__H
#define MENUHANDLER__H

#include "user.h"
#include "matchHandler.h"
#include "userHandler.h"

class MenuHandler {
private:
    MatchHandler &matches;    
    std::vector<UserHandler*> menuHandlers;
    void delete_finish_clients(std::vector<UserHandler*> &menuHandlers);
public:
    MenuHandler(MatchHandler &mH);
    ~MenuHandler();

    void addUser(User *user);
};

#endif