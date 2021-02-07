#include "userHandler.h"

UserHandler::UserHandler(User *user, MatchHandler &matches):
    is_running(true),
    matches(matches),
    user(user)
{
            std::cout << "userHandler: meto un usuario" << std::endl;

}

UserHandler::~UserHandler(){
    if(user != NULL){
        delete(user);
        user = NULL;
    }
}

void UserHandler::operator()(){
    this->start();
}

void UserHandler::run(){
    std::stringstream welcomeMessage;
    welcomeMessage <<  "Bienvenido a Wolfestein3D!\n\n";

        std::cout << "userHandler: empiezo a corre" << std::endl;
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

void UserHandler::processInput(){
    menu_event_t event;
    user->readMenuEvent(event);

    if(event.event == NEW_NAME){
        std::cout << "llego NEWNAME" << std::endl;
        changeUserName(event.info);
    }
    if(event.event == JOIN){
        std::cout << "llego JOIN" << std::endl;
        
        addUserToMatch(event.info);
    }
    if(event.event == GET_MATCHES){
        std::cout << "se pidio partidas"     << std::endl;
        sendMatches();
    }
    if(event.event == NEW_MATCH){
        std::cout << "llego NEW_MATCH" << std::endl;
        newMatch(event.info);
        addUserToMatch(event.info);
    }
}

void UserHandler::changeUserName(std::string &newName){
    user->changeName(newName);
}

void UserHandler::newMatch(std::string &matchName){
    matches.newMatch(matchName);
}

void UserHandler::addUserToMatch(std::string matchName){
    bool wasAbleToJoin = false;
    wasAbleToJoin = matches.addUserToMatch(user, matchName);
    if(wasAbleToJoin){
        user = NULL;
        stop();
    }
}

void UserHandler::sendMatches(){
    std::stringstream matchesList;
    matches.getMatchList(matchesList);
    std::cout << "se manda partidas:" << matchesList.str() << "." << std::endl;
    menu_event_t anEvent;
    anEvent.event = GET_MATCHES;
    anEvent.info = matchesList.str();
    user->sendString(anEvent.info);
}

bool UserHandler::is_dead(){
    return !is_running;
}

void UserHandler::stop(){
    is_running = false;
}
