#include "clientTransmitter.h"

ClientTransmitter::ClientTransmitter(Socket &socket):
    socket(socket),
    is_running(true),
    atMenus(true)
{}

ClientTransmitter::ClientTransmitter(ClientTransmitter&& other):
    socket(other.socket)
{}
    // ~Transmitter(){}
void ClientTransmitter::operator()()
{
    this->start(); 
}

// Envia comandos
void ClientTransmitter::run()
{
    while(is_running == true)
    {
        std::string command;
        getline(std::cin, command);

        // Por ahora no ingresar nada es lo que detiene el hilo del transmitter, y esto cierra al cliente.
        if(command.length() == 0)
        {
            is_running = false;
        }
        std::stringstream response(command);
        uint32_t length = response.str().length();
        const size_t SIZE_OF_UINT32 = 4;
        length = htonl(length);
        socket.send((char *) &length, SIZE_OF_UINT32);
        socket.send(response.str().data(), response.str().length());   
    }
}

bool ClientTransmitter::isRunning(){
    return is_running;
}

void ClientTransmitter::isAtMenu()
{
    atMenus = true;
}

void ClientTransmitter::isInMatch()
{
    atMenus = false;
}
