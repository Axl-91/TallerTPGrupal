#ifndef SERVER__T
#define SERVER

#include <sstream>
#include <string>
#include <iostream>
#include "thacceptor.h"
#include "menuHandler.h"
#include "matchHandler.h"

class Server{
private:
    MenuHandler menuHandler;
    MatchHandler matchHandler;
    ThAcceptor acceptor;
public:
    Server(const char *service);
    void run();
};

#endif