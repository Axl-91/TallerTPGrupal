#include "client.h"

Client::Client(const char *host_name, const char *port):
    atMenus(true),
    connectedToMatch(false),
    transmitter(s,q),
    receiver(s,lvl2, uQ),
    eHandler(q),
    is_running(false)
{
    std::cout << "empiezo a construir client" << std::endl;
    s.connect(host_name, port);
    std::cout << "conecte client" << std::endl;
    if(!s.isConnected())
        return;
    transmitter();
    receiver();
    eHandler();
    std::cout << "termine de construir client" << std::endl;

}

Client::~Client(){
    std::cout << "\n\n destructor client" << std::endl;
    is_running = false;
    if(transmitter.isRunning()){
        transmitter.stop();
        std::cout << "hice stop a transmitter" << std::endl;
        transmitter.join();
    }
    if(!receiver.isDead()){
        receiver.stop();
        std::cout << "hice stop a receiver" << std::endl;
    }
    receiver.join();
    if(!eHandler.isDead()){
        eHandler.stop();
        std::cout << "hice stop a ehandler" << std::endl;
    }
    eHandler.join();
        std::cout << "salgo de destructor" << std::endl;

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
            // if(transmitter.isRunning() == false){
            //     is_running = false;
            //     receiver.stop();
            //     eHandler.stop();
            //     s.shutdown_read();
            //     s.shutdown_writing();
                // std::cout << "is running es false" << std::endl;
            // }    
            if(receiver.isInMatch() == true && is_running == true){
                std::cout << "client: isInMatch" << std::endl;
                
                std::cout << "___________________________________ \n" << std::endl;
                Game game(640, 480, lvl2, uQ);
                // SDL_EventHandler eventHandler;
                //game.setFullScreen();
                std::cout << "___________________________________ \n" << std::endl;

                while (!game.isGameOver() && is_running == true){
                    // event = eventHandler.pollEvent();
                    // event_t event;
                    // while(!q.isEmpty()){
                    //     event = q.pop();
                    //     game.receiveEvent(event);

                    // }
                    if(eHandler.finished()){
                        game.quitGame();
                        is_running = false;
                        continue;
                        // MATAR TODO
                    }

                    // game.pollEvent();
                    // if(anUpdate.mapChangeAvailable == true){
                    //     game.updateMap(anUpdate.mapChange);
                    //     anUpdate.mapChangeAvailable = false;
                    // }
                    
                    // game.updatePlayer(anUpdate.playerUpdate);
                    // std::cout << "hago game update" << std::endl;
                    game.update();

                    if(receiver.matchFinished()){
                        game.quitGame();
                        receiver.quitMatch();
                        is_running = false;
                        s.shutdown_read();
                        s.shutdown_writing();
                        continue;
                    }
                    game.render();
                    // SDL_Delay(60);
                    sleep(1/60);
                }
            }
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
