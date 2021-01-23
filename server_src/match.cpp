#include "match.h"

Match::Match(std::string matchName):
    is_running(true),
    name(matchName)
{}


Match::~Match(){
    for (size_t i = 0; i < users.size(); i++){

        if(users.at(i)->hasStarted()){
            users.at(i)->stop();
            users.at(i)->join();    
        }
        delete(users.at(i));
    }
}

void Match::operator()(){
    this->start();
}

void Match::run(){
    try{
        while(is_running)
        {
            updateUsers();
        }
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en Match.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

void Match::stop(){
    is_running = false;
}

void Match::addUser(User* user){
    user->setProtectedQueue(&q);
    users.emplace_back(user);
    user->start();

    std::stringstream welcome;
    welcome << "Te uniste a la partida: " << name << std::endl;
    welcome << "Bienvenido!\nPodes chatear con otros jugadores en la sala." << std::endl;
    welcome << "Cantidad de jugadores en la sala: " << users.size() << std::endl;
    user->sendGameUpdate(welcome);
}

// Envio el contenido de la cola a los clientes
void Match::updateUsers(){
    std::stringstream auxStream;
    while(!q.isEmpty()){
        std::string frase = q.pop();
        auxStream << frase << std::endl;
    }
    for(auto user:users){
        user->sendGameUpdate(auxStream);
    }
}

std::string Match::getName(){
    return name;
}

bool Match::started(){
    return gameStarted;
}

bool Match::isUserNameAvailable(std::string aName){
    for(auto user:users){
        if(user->getName() == aName)
            return false;
    }
    return true;
}
