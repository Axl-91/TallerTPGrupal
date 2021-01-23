#include "clientReceiver.h"

ClientReceiver::ClientReceiver(Socket &socket):
    socket(socket),
    is_running(true),
    atMenus(true)
{}

ClientReceiver::ClientReceiver(ClientReceiver&& other):
    socket(other.socket)
{}
void ClientReceiver::operator()(){ 
    this->start(); 
}

void ClientReceiver::run(){
    try{
        while(is_running == true){
            receiveGame();
        }
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en User.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

void ClientReceiver::receiveMenuOption(){}

void ClientReceiver::receiveGame(){
    uint32_t length = 0;
    const size_t SIZE_OF_UINT32 = 4;

    socket.receive((char *) &length, SIZE_OF_UINT32);
    length = ntohl(length);
    if(length == 0){
        is_running = false;
    }
    std::vector<char> buffer(length+1, 0);
    socket.receive(buffer.data(), length);
    std::string response = buffer.data();
    std::cout << response;
}

// Se usa al finalizar el ingreso de input
void ClientReceiver::stop(){
    is_running = false;
}

void ClientReceiver::isAtMenu(){
    atMenus = true;
}

void ClientReceiver::isInMatch(){
    atMenus = false;
}
