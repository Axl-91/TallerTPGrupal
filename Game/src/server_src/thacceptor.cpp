#include "thacceptor.h"

ThAcceptor::ThAcceptor(const char *service, MenuHandler& mH):
    keep_accepting(true),
    menuHandler(mH)
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
        while (keep_accepting){
            std::cout << "acepto user" << std::endl;
            Socket clSocket(accept());
            std::cout << "acepte user" << std::endl;
            User *user = new User(std::move(clSocket));
            menuHandler.addUser(user);
        }

    } catch (const AcceptorClosed &e){ /* Finaliza ejecución de ThAcceptor */
    } catch (const std::exception &e){
        std::cerr << "Error encontrado en thAcceptor.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) { // ellipsis: catch anything
        printf("thAcceptor: Unknown error!");
    }
}
