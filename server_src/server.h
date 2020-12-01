#ifndef SERVER__T
#define SERVER

#include <sstream>
#include <string>
#include <iostream>
#include "thacceptor.h"
// #include "protectedResources.h"
class Server{
private:
    ThAcceptor acceptor;
    // ProtectedResources resources;
public:
    Server(const char *service);
    void run();
    // void bind_and_listen(const char *service);
    // void send_msg(std::stringstream& buf);
    // void receive_msg(std::stringstream& petition);
    // void accept();
};

#endif