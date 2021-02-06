#include "menuHandler.h"

MenuHandler::MenuHandler(User *user, MatchHandler &matches):
    is_running(true),
    matches(matches),
    user(user)
{}

MenuHandler::~MenuHandler(){
    if(user != NULL){
        delete(user);
        user = NULL;
    }
}

void MenuHandler::operator()(){
    this->start();
}

void MenuHandler::run(){
    std::stringstream welcomeMessage;
    welcomeMessage <<  "Bienvenido a Wolfestein3D!\n\n";

    // user->sendGameUpdate(welcomeMessage);
    try{
        while(is_running){
            std::string instrucciones = "Ingrese\t\t\t\t\t\t\tNombre de usuario: " + user->getName() + "\n\
                cambiarnombre - para cambiar nombre de usuario.\n\
                verpartidas - para ver las partidas disponibles.\n\
                unirme - para ingresar el nombre de la partida a la que desea unirse.\n\
                crear - para crear una nueva partida.\n\
                quit - para desconectarse del juego.\n\n";
                std::stringstream instr(instrucciones);
                // user->sendGameUpdate(instr);

                processInput();
        }
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en menuHandler.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

void MenuHandler::processInput(){
    event_t command;
    user->readInput(command);

    // if(command == "Se cerro receive")
    //     stop();
    // if(command == "quit")
    //     stop();
    // if(command.length() == 0){
    //     sleep(1/60);
    //     std::cout << "llego cadena vacia" << std::endl;
    //     return;
    // }
    // if(command == "cambiarnombre")
    //     changeUserName();
    if(command == UNIRME)
        joinMatch();
    // if(command == "verpartidas")
    //     sendMatches();
    if(command == NEW_MATCH)
        newMatch();
}

void MenuHandler::changeUserName(){
    std::stringstream changeUserNameMessage;
    changeUserNameMessage << "Ingrese su nuevo nombre de usuario:\n";
    // user->sendGameUpdate(changeUserNameMessage);

    std::string newUserName;
    // user->readInput(newUserName);
    // user->changeName(newUserName);
}

void MenuHandler::joinMatch(){
    event_t matchName;
    std::stringstream typeMatchName;
    typeMatchName << "Ingrese el nombre de la partida a la que desee unirse:\n";
    // user->sendGameUpdate(typeMatchName);
    user->readInput(matchName);
    if(matchName == PICHIWAR)
        addUserToMatch("pichiwar");
    if(matchName == ASD)
        addUserToMatch("asd");
    return;
}

void MenuHandler::newMatch(){
    // std::string matchName;

    std::stringstream newMatchText;
    newMatchText << "Ingrese el nombre de la nueva partida: \n\n";
    event_t matchName;
    user->readInput(matchName);
    if(matchName == ASD)
    // addUserToMatch("asd");
    matches.newMatch("asd");
}

void MenuHandler::addUserToMatch(std::string matchName){
    bool wasAbleToJoin = false;
    wasAbleToJoin = matches.addUserToMatch(user, matchName);
    if(wasAbleToJoin){
        user = NULL;
        stop();
    }
}

void MenuHandler::sendMatches(){
    std::stringstream matchesList;
    matches.getMatchList(matchesList);

    // user->sendGameUpdate(matchesList);
}

bool MenuHandler::is_dead(){
    return !is_running;
}

void MenuHandler::stop(){
    is_running = false;
}
