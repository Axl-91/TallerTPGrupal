#ifndef SERVER__T
#define SERVER__T

#include <sstream>
#include <string>
#include <iostream>
#include "thacceptor.h"
#include "menuHandler.h"
#include "matchHandler.h"
#include "AILuaScript.h"
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