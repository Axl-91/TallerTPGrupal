#include "server.h"
#include <iostream>
int main(int argc, char* argv[]){

    Server server(argv[1]);
    try{
    server.run();
    } catch(...) {
        std::cerr << "pasaron cosas" << std::endl;
    }
    return 0;
}