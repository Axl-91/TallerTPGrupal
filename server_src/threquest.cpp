#include "threquest.h"

ThRequest::ThRequest(Socket socket):
    s(std::move(socket)),
    is_running(true)
{}

ThRequest::~ThRequest(){
}

void ThRequest::operator()(){
    this->start();
}

void ThRequest::run(){
    try {
        std::stringstream response;
        response << "respuesta";
        std::stringstream petition;
        Receiver receiver(s, petition);
        Transmitter transmitter(s, response);
        receiver();
        transmitter();
        std::cout << "recibio" << std::endl;

        transmitter.join();
        receiver.join();

        is_running = false;
        s.shutdown_writing();
    } catch (const std::exception &e){
        std::cerr << "Excepcion en ThRequest.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

bool ThRequest::is_dead(){
    return !is_running;
}

void ThRequest::send_response(std::stringstream& response){
    std::string respuesta = "Recibi";
    uint32_t length = respuesta.length();
    const size_t SIZE_OF_UINT32 = 4;
    length = htonl(length);
	s.send((char *) &length, SIZE_OF_UINT32);
    s.send(respuesta.data(), respuesta.length()); 

}

void ThRequest::receive_petition(std::stringstream& petition){
    uint32_t length = 0;
    size_t SIZE_OF_UINT32 = 4;

    s.receive((char *) &length, SIZE_OF_UINT32);
    length = ntohl(length);

    std::vector<char> buffer(length+1, 0);
    s.receive(buffer.data(), length);

    std::string response = buffer.data();
    std::cout << response;
}
