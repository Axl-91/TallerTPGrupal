#ifndef SERVER__T
#define SERVER

#include <sstream>
#include <string>
#include <iostream>
#include "thacceptor.h"

class Server{
private:
    ThAcceptor acceptor;
public:
    Server(const char *service);
    void run();
};

#endif