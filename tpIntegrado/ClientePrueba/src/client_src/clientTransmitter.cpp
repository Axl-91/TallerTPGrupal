#include "clientTransmitter.h"

ClientTransmitter::ClientTransmitter(Socket &socket, ProtectedQueue<event_t> &gQ, ProtectedQueue<menu_event_t> &mQ):
    socket(socket),
    is_running(false),
    atMenus(true),
    gameEventQ(gQ),
    menuEventQ(mQ)
{}

    // ~Transmitter(){}
void ClientTransmitter::operator()(){
    this->start(); 
}

// Envia comandos
void ClientTransmitter::run(){
    is_running = true;
    try{
        while(is_running == true){
            if(!gameEventQ.isEmpty())
                sendGameEvent();
            if(!menuEventQ.isEmpty())
                sendMenuEvent();
        }
    } catch (const SocketError &e){
        std::cerr << "Excepcion en clientTransmitter.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &e){
        std::cerr << "Excepcion en clientTransmitter.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    } 
}

void ClientTransmitter::sendGameEvent(){
    event_t event;
    event = NO_EVENT;
    
    event = gameEventQ.pop();

    if(event!=NO_EVENT)
        socket.send((char*) &event, sizeof(event_t));    
}

void ClientTransmitter::sendMenuEvent(){
    menu_event_t event;
    event.event = NO_EVENT;
    
    event = menuEventQ.pop();
    if(event.event!=NO_EVENT)
        socket.send((char*) &event.event, sizeof(event_t));  

    uint32_t length = event.info.length();
    const size_t SIZE_OF_UINT32 = 4;
    length = htonl(length);
    socket.send((char *) &length, SIZE_OF_UINT32);
    if(length != 0)
        socket.send(event.info.data(), event.info.length()); 
}

void ClientTransmitter::stop(){
    is_running = false;
}

bool ClientTransmitter::isRunning(){
    return is_running;
}

void ClientTransmitter::isAtMenu(){
    atMenus = true;
}

void ClientTransmitter::isInMatch(){
    atMenus = false;
}
