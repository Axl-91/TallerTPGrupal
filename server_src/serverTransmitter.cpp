#include "serverTransmitter.h"

ServerTransmitter::ServerTransmitter(Socket &socket):
    socket(socket)
{}

ServerTransmitter::ServerTransmitter(ServerTransmitter&& other):
    socket(other.socket)
{}
    // ~Transmitter(){}
void ServerTransmitter::send(std::stringstream &game){
    if(game.str().length() == 0)
        return;
    uint32_t length = game.str().length();
    const size_t SIZE_OF_UINT32 = 4;
    length = htonl(length);
    socket.send((char *) &length, SIZE_OF_UINT32);
    socket.send(game.str().data(), game.str().length());   
}
