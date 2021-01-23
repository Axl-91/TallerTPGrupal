#include "user.h"

User::User(Socket socket):
    s(std::move(socket)),
    transmitter(s),
    receiver(s),
    userIsRunning(true),
    started(false),
    userName("randomUser123")
{}

void User::operator()(){
    this->start();
}

void User::setProtectedQueue(ProtectedQueue *q){
    this->q = q;
}

void User::run(){
    started = true;
    try {
        while(userIsRunning){
            std::string input;
            readInput(input);
            if(input == "Se cerro receive"){
                userIsRunning = false;
                continue;
            }
            q->push(input);
        }
    } catch (const SocketError &e){
        std::cerr << "Excepcion en ServerReceiver.run()" << std::endl;
    } catch (const std::exception &e){
        std::cerr << "Excepcion en User.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

bool User::is_dead(){
    return !userIsRunning;
}
bool User::hasStarted(){
    return started;
}
void User::readInput(std::string &input){
    receiver.readInput(input);
}

void User::stop(){
    userIsRunning = false;
}

void User::changeName(std::string newName){
    userName = newName;
}

void User::sendGameUpdate(std::stringstream& game){
    transmitter.send(game);
}

std::string User::getName(){
    return userName;
}
