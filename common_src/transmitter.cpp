#include "transmitter.h"

Transmitter::Transmitter(Socket &socket, std::stringstream& response):
    socket(socket),
    response(response)
{}
    // ~Transmitter(){}
void Transmitter::operator()(){
    this->start(); 
}

void Transmitter::run(){

    uint32_t length = response.str().length();
    const size_t SIZE_OF_UINT32 = 4;
    length = htonl(length);
    socket.send((char *) &length, SIZE_OF_UINT32);
    socket.send(response.str().data(), response.str().length());
}