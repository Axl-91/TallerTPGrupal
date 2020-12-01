#include "client.h"

Client::Client(const char *host_name, const char *port){
    connect(host_name, port);
}

void Client::read_petition(){
	std::string line;
	while (getline(std::cin, line)){
    	petition << line;
	}
 }

void Client::connect(const char *host_name, const char *port){
	s.connect(host_name, port);
}

void Client::shutdown_writing(){
	s.shutdown_writing();
}

void Client::run(){
    read_petition();
    Transmitter transmitter(s, petition);
    transmitter();
    Receiver receiver(s, petition);
    receiver();

    transmitter.join();
    receiver.join();
    shutdown_writing();
}
