#include "receiver.h"

Receiver::Receiver(Socket &socket, std::stringstream& response):
    socket(socket),
    response(response)
{}

    // ~Receiver(){}
void Receiver::operator()(){ 
    this->start(); 
}

void Receiver::run(){
    uint32_t length = 0;
    const size_t SIZE_OF_UINT32 = 4;

    socket.receive((char *) &length, SIZE_OF_UINT32);
    length = ntohl(length);
    
    std::vector<char> buffer(length+1, 0);
    socket.receive(buffer.data(), length);
    std::string response = buffer.data();
    std::cout << response;
}