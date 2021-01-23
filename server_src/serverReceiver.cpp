#include "serverReceiver.h"

ServerReceiver::ServerReceiver(Socket &socket):
    socket(socket)
{}

ServerReceiver::ServerReceiver(ServerReceiver&& other):
    socket(other.socket)
{}

void ServerReceiver::readInput(std::string &input){
    try{
        uint32_t length = 0;
        const size_t SIZE_OF_UINT32 = 4;

        socket.receive((char *) &length, SIZE_OF_UINT32);
        length = ntohl(length);

        // Si recibe una cadena vacia, el cliente se desconecto, por lo que elimino el user correspondiente del lado server.
        if(length == 0){
            stop();
            return;
        }
        std::vector<char> buffer(length+1, 0);
        socket.receive(buffer.data(), length);
        input = buffer.data();
    } catch (const SocketError &e){
        input = "Se cerro receive";
        std::cerr << "Excepcion en ServerReceiver.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &e){
        std::cerr << "Excepcion en ServerReceiver.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

void ServerReceiver::stop(){
    socket.shutdown_read();
}
