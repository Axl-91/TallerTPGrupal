#include "clientTransmitter.h"

ClientTransmitter::ClientTransmitter(Socket &socket, ProtectedEventQueue &q):
    socket(socket),
    is_running(false),
    atMenus(true),
    q(q)
{}

ClientTransmitter::ClientTransmitter(ClientTransmitter&& other):
    socket(other.socket),
    q(other.q)
{}
    // ~Transmitter(){}
void ClientTransmitter::operator()()
{
    this->start(); 
}

void getCommand(ProtectedEventQueue &q, std::string command){
    
}

// Envia comandos
void ClientTransmitter::run()
{
    is_running = true;
    try{

        std::cout << "Entro a clien transmitter" << std::endl;
        event_t event;
        std::string command;

        getline(std::cin, command);
        if(command=="unirme")
            event = UNIRME;
        socket.send((char*) &event, sizeof(event_t));

        getline(std::cin, command);
        if(command=="pichiwar")
            event = PICHIWAR;
        socket.send((char*) &event, sizeof(event_t));


        while(is_running == true){
            event = NO_EVENT;
            
            if(!q.isEmpty())
                event = q.pop();

            if(event==NO_EVENT){
                sleep(1/60);
                continue;    
            }
            socket.send((char*) &event, sizeof(event_t));
        }
    } catch (const SocketError &e){
        std::cerr << "Excepcion en clientTransmitter.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &e){
        std::cerr << "Excepcion en clientTransmitter.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    } 
}

void ClientTransmitter::stop(){
    is_running = false;
}

void funcionVieja(){
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
