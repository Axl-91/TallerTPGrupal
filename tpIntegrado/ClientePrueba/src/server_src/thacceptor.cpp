#include "thacceptor.h"

ThAcceptor::ThAcceptor(const char *service):
    keep_accepting(true)
{
    acceptor_socket.bind_and_listen(service);
}

Socket ThAcceptor::accept(){
    return std::move(acceptor_socket.accept());
}
void ThAcceptor::operator()(){
    this->start();
}
void ThAcceptor::stop_accepting(){
    keep_accepting = false;
    acceptor_socket.shutdown_read();
    acceptor_socket.shutdown_writing();
}

void ThAcceptor::run(){
    try {
        MatchHandler matches;

        matches.newMatch("pichiwar");
        while (keep_accepting){
            std::cout << "acepto user" << std::endl;
            Socket clSocket(accept());
            std::cout << "acepte user" << std::endl;
            User *user = new User(std::move(clSocket));
            MenuHandler *menuHandler = new MenuHandler(user, matches);
            (*menuHandler)();
            threads.push_back(menuHandler);
            delete_finish_clients(threads);
        }

    } catch (const AcceptorClosed &e){ /* Finaliza ejecución de ThAcceptor */
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en thAcceptor.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("thAcceptor: Unknown error!");
    }

    for (size_t i = 0; i < threads.size(); i++){
        threads.at(i)->stop();
        threads.at(i)->join();    
        delete(threads.at(i));
    }
}

void ThAcceptor::delete_finish_clients(std::vector<MenuHandler*>& threads){
    std::vector <MenuHandler*> temp;
    std::vector <MenuHandler*>::iterator it = threads.begin();
    for (; it != threads.end() ; ++it){
        if ((*it)->is_dead()){
            (*it)->join();
            delete(*it);
            *it = NULL;
        } else {
            temp.push_back(*it);
        }
    }
    threads.swap(temp);
}
