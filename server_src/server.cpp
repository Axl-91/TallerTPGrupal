#include "server.h"

Server::Server(const char *service):
    acceptor(service)
{}

void Server::run(){
    std::string input;
    bool keep_accepting = true;

    acceptor();
    
    while (keep_accepting){
        std::cin >> input;
        if(input == "q"){
            keep_accepting = false;
            acceptor.stop_accepting();
        }
    }
    acceptor.join();
}

