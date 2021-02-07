#include "menuHandler.h"

MenuHandler::MenuHandler(MatchHandler &mH):
    matches(mH)
{}

MenuHandler::~MenuHandler(){
    for (size_t i = 0; i < menuHandlers.size(); i++){
        menuHandlers.at(i)->stop();
        menuHandlers.at(i)->join();    
        delete(menuHandlers.at(i));
    }
}

void MenuHandler::addUser(User *user){
    UserHandler *userHandler = new UserHandler(user, matches);
    (*userHandler)();
    menuHandlers.push_back(userHandler);
                                std::cout << "Menuhandler.19: agregue un usuario" << std::endl;
    delete_finish_clients(menuHandlers);
}

void MenuHandler::delete_finish_clients(std::vector<UserHandler*>& menuH){
    std::vector <UserHandler*> temp;
    std::vector <UserHandler*>::iterator it = menuH.begin();
    for (; it != menuH.end() ; ++it){
        if ((*it)->is_dead()){
            (*it)->join();
            delete(*it);
            *it = NULL;
        } else {
            temp.push_back(*it);
        }
    }
    menuH.swap(temp);
}