#include "thacceptor.h"

ThAcceptor::ThAcceptor(const char *service):
    keep_accepting(true)
{
    bind_and_listen(service);
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

void ThAcceptor::bind_and_listen(const char *service){
    acceptor_socket.bind_and_listen(service);
}

void ThAcceptor::run(){
    try {
        while (keep_accepting){
            Socket clSocket(accept());

            ThRequest *request = new ThRequest(std::move(clSocket));
            (*request)();
            threads.push_back(request);
            delete_finish_clients(threads);
        }
    } catch (const AcceptorClosed &e){ /* Finaliza ejecución de ThAcceptor */
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en ThAcceptor.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }

    for (size_t i = 0; i < threads.size(); i++){
        threads.at(i)->join();    
        delete(threads.at(i));
    }
}

void ThAcceptor::delete_finish_clients(std::vector<ThRequest*>& threads){
    std::vector <ThRequest*> temp;
    std::vector <ThRequest*>::iterator it = threads.begin();
    for (; it != threads.end() ; ++it){
        if ((*it)->is_dead()){
            (*it)->join();
            delete(*it);
        } else {
            temp.push_back(*it);
        }
    }
    threads.swap(temp);
}
