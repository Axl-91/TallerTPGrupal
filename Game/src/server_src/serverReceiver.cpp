#include "serverReceiver.h"

ServerReceiver::ServerReceiver(Socket &socket):
    socket(socket),
    is_running(true)
{}

ServerReceiver::ServerReceiver(ServerReceiver&& other):
    socket(other.socket)
{}

void ServerReceiver::readMenuEvent(menu_event_t &menuEvent){
    readGameEvent(menuEvent.event);

    uint32_t length = 0;
    const size_t SIZE_OF_UINT32 = 4;

    socket.receive((char *) &length, SIZE_OF_UINT32);
    length = ntohl(length);
    if(length == 0){
        menuEvent.info = "";
        return;
    }
    std::vector<char> buffer(length+1, 0);
    socket.receive(buffer.data(), length);
    menuEvent.info = buffer.data();

}

void ServerReceiver::readGameEvent(event_t &input){
    if(is_running == false)
        return;
    try{
        socket.receive((char*) &input, sizeof(input));
    } catch (const SocketClosed &e){
        std::cerr << "Excepcion en ServerReceiver.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        is_running = false;
    }
}

void ServerReceiver::stop(){
    socket.shutdown_read();
    is_running = false;
}

bool ServerReceiver::finished(){
    return !is_running;
}