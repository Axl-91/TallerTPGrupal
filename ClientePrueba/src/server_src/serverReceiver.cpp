#include "serverReceiver.h"

ServerReceiver::ServerReceiver(Socket &socket):
    socket(socket),
    is_running(true)
{}

ServerReceiver::ServerReceiver(ServerReceiver&& other):
    socket(other.socket)
{}

void ServerReceiver::readInput(event_t &input){
    try{
        // std::cout << "serverReceiver: leo input" << std::endl;

        socket.receive((char*) &input, sizeof(input));
        // std::cout << input << std::endl;

        // event_t event;
        // socket.receive((char*) &event, sizeof(event));
    
        // std::cout << event << std::endl;

    } catch (const SocketClosed &e){
        std::cerr << "Excepcion en ServerReceiver.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        is_running = false;
    }
}

void ServerReceiver::stop(){
    socket.shutdown_read();
}

bool ServerReceiver::finished(){
    return !is_running;
}