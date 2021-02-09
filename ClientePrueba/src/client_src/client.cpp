#include "client.h"

Client::Client(const char *host_name, const char *port):
    atMenus(true),
    connectedToMatch(false),
    transmitter(s,gameEventQ, menuEventQ),
    receiver(s,lvl2, gameUpdateQ, menuResponseQ),
    eHandler(gameEventQ),
    is_running(false)
{
    s.connect(host_name, port);
    if(!s.isConnected())
        return;
    transmitter();
    // receiver();
}

Client::~Client(){
    is_running = false;
    if(transmitter.isRunning()){
        transmitter.stop();
        transmitter.join();
    }
    if(!receiver.isDead()){
        receiver.stop();
    }
    receiver.join();
    if(!eHandler.isDead()){
        eHandler.stop();
    }
    eHandler.join();
}

void Client::read_petition(){
	std::string line;
	while (getline(std::cin, line))
    {
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
    is_running = true;
    
    try{
        // Debe transmitir el user input. Por ahora es strings, eventualmente se cambia a eventos.

        // Recibe actualmente todo lo envia por quienes estan en mismo match. Cambiar despues a enviar modelo.
        
        while(is_running == true){            
            int winLargo = 640;
            int winAlto = 480;
            {
                Menu menu(menuEventQ, receiver, winLargo, winAlto);
                while (!menu.quitGame() && !menu.createGame() && !menu.joinGame()){
                    menu.pollEvent();
                    menu.render();
                    // sleep (1/60);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
            receiver();

            while(!receiver.isInMatch()){
                sleep(1/60);
            }
            eHandler();

            std::cout << "client: isInMatch" << std::endl;
            
            std::cout << "___________________________________ \n" << std::endl;
            Game game(winLargo, winAlto, lvl2, gameUpdateQ);

            std::cout << "___________________________________ \n" << std::endl;
            game();
            while (!game.isGameOver() && is_running == true){

                if(eHandler.finished()){
                    game.quitGame();
                    is_running = false;
                    continue;
                    // MATAR TODO
                }


                if(receiver.matchFinished()){
                    game.quitGame();
                    receiver.quitMatch();
                    is_running = false;
                    s.shutdown_read();
                    s.shutdown_writing();
                    continue;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(40));
                // SDL_Delay(60);

            }
            game.join();
            
        }

    }  catch (const SocketError &e){
        std::cerr << "Excepcion en client.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        
    } catch (const std::exception &e){
        std::cerr << "Excepcion en client.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    } 
    std::cout << "salgo de run cliente " << std::endl;
}


void Client::isAtMenu(){
    atMenus = true;
}

void Client::isInMatch(){
    atMenus = false;
}
