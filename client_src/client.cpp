#include "client.h"

Client::Client(const char *host_name, const char *port):
    atMenus(true)
{
    connect(host_name, port);
}

void Client::read_petition()
{
	std::string line;
	while (getline(std::cin, line))
    {
    	petition << line;
	}
 }

void Client::connect(const char *host_name, const char *port)
{
	s.connect(host_name, port);
}

void Client::shutdown_writing()
{
	s.shutdown_writing();
}

void Client::run()
{
    std::atomic<bool> is_running(true);
    ClientTransmitter transmitter(s);
    ClientReceiver receiver(s);

    // Debe transmitir el user input. Por ahora es strings, eventualmente se cambia a eventos.
    transmitter();

    // Recibe actualmente todo lo envia por quienes estan en mismo match. Cambiar despues a enviar modelo.
    receiver();

    while(is_running == true)
    {
        if(transmitter.isRunning() == false)
        {
            is_running = false;
            receiver.stop();
            s.shutdown_read();
            s.shutdown_writing();
        }    
    }
    transmitter.join();
    receiver.join();
    shutdown_writing();
}

void Client::isAtMenu()
{
    atMenus = true;
}

void Client::isInMatch()
{
    atMenus = false;
}
