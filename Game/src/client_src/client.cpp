#include "client.h"

Client::Client(const char *host_name, const char *port):
    gameStarted(false),
    connectedToMatch(false),
    // transmitter(s,gameEventQ, menuEventQ),
    // receiver(s,lvl2, gameUpdateQ, menuResponseQ),
    transmitter(s,gameEventQ),
    receiver(s,lvl2, gameUpdateQ),
    eHandler(gameEventQ),
    is_running(false)
{
    s.connect(host_name, port);
    if(!s.isConnected())
        return;
}

Client::~Client(){
    gameUpdateQ.close();
    gameEventQ.close();
    is_running = false;
    if(gameStarted){
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
        while(is_running == true){            
            int winLargo = 640;
            int winAlto = 480;
            bool fullscreen = false;
            runMenu(winLargo, winAlto, fullscreen);

            if(!gameStarted){
                is_running = false;
                continue;
            }

            runGame(winLargo, winAlto, fullscreen);
        }
    }  catch (const SocketError &e){
        std::cerr << "Excepcion en client.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &e){
        std::cerr << "Excepcion en client.run()" << std::endl;
        std::cerr << e.what() << std::endl;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    } 
}

void Client::runMenu(int &winLargo, int &winAlto, bool &fullscreen){
    Menu menu(receiver, transmitter, winLargo, winAlto, fullscreen);

    while (!menu.quitGame() && !menu.createGame() && !menu.joinGame()){
    // while (!menu.leftMenu()){
        menu.pollEvent();
        menu.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }
    gameStarted = menu.joinedMatch();
}

void Client::runGame(int &winLargo, int &winAlto, bool &fullScreen){
    receiver();
    std::cout<<"run game"<<std::endl;

    while(!receiver.isInMatch()){
        sleep(1/60);
    }
    std::cout<<"run game: empezamos match"<<std::endl;
    eHandler();
    transmitter();

    Game game(winLargo, winAlto, fullScreen, lvl2, gameUpdateQ);
    game();

    while (!game.isGameOver() && is_running == true){

        if(eHandler.finished()){
            game.quitGame();
            is_running = false;
            gameUpdateQ.close();
            // menuEventQ.close();
            continue;
            // MATAR TODO
        }

        if(receiver.matchFinished()){
            game.quitGame();
            receiver.quitMatch();
            is_running = false;
            gameUpdateQ.close();
            s.shutdown_read();
            s.shutdown_writing();
            continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }   
    game.join();
}
