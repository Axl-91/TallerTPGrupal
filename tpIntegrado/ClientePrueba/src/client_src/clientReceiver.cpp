#include "clientReceiver.h"

ClientReceiver::ClientReceiver(Socket &socket, 
    std::vector<std::vector<int>> &lvl2, 
    Player_t &p,
    Map_change_t &mapC):
    socket(socket),
    is_running(false),
    atMenus(true),
    inMatch(false),
    lvl2(lvl2),
    matchEnded(false),
    player(p),
    mapChange(mapC)
{}

ClientReceiver::ClientReceiver(ClientReceiver&& other):
    socket(other.socket),
    lvl2(other.lvl2),
    player(other.player),
    mapChange(other.mapChange)
{}
void ClientReceiver::operator()(){ 
    this->start(); 
}

void ClientReceiver::run(){
    is_running = true;
    try{
        while(is_running == true){
            receiveGame();
        }
        
    } catch (const SocketClosed &e){
        std::cerr << "Excepcion en clientReceiver.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        is_running = false;
    }  catch (const std::exception &e){
        std::cerr << "Excepción encontrada en clientReceiver.run()" << std::endl;
        std::cerr << e.what() << std::endl;
        // throw SocketError("Se cierra Receiver");
        return;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }
}

bool ClientReceiver::matchFinished(){
    return matchEnded;
}

bool ClientReceiver::isDead(){
    return !is_running;
}

void ClientReceiver::receiveMenuOption(){}

void ClientReceiver::receiveGame(){
    uint32_t length = 0;
    const size_t SIZE_OF_UINT32 = 4;
    // std::cout << "Entro a receiver"  << std::endl;

    socket.receive((char *) &length, SIZE_OF_UINT32);
    length = ntohl(length);
    if(length == 0){
        is_running = false;
    }
    std::vector<char> buffer(length+1, 0);
    socket.receive(buffer.data(), length);
    std::string response = buffer.data();
    // std::cout << "ClientReceiver(), recibo mensaje: \n" << response << std::endl;

    if(response == "mapa"){
     std::cout<<"client.receive cargo el mapa"<<std::endl;
        receiveMap();
    }
    if(response == "playerInfo"){
        receivePlayerInfo();
        // std::cout << "Receiver::Recibi player tag: " << player.ID  << std::endl;
    }

    if(response == "mapChange"){
        receiveMapChange();
    }

    if(response == "GAME_QUIT"){
        matchEnded = true;
    }

    // if(response == "ID"){

    // }
}

void ClientReceiver::receivePlayerInfo(){
    Player_t aux;

    socket.receive((char *) &aux, sizeof(Player_t));

    player = aux;
}

void ClientReceiver::receiveMapChange(){
    Map_change_t aux;
    //  std::cout<<"receive map change"<<std::endl;

    socket.receive((char *) &aux, sizeof(Map_change_t));
    std::cout<<aux.value<<std::endl;

    std::cout<<aux.value<<std::endl;
    mapChange = aux;
}

void printVector(std::vector<std::vector<int>> &lvl2){
    for(auto v:lvl2){
        std::cout << v.size() << std::endl;
        for(auto num:v)
            std::cout << num;
        std::cout << std::endl;
    }
}
void ClientReceiver::receiveMap(){
    std::cout << "Recibo mapa" << std::endl;
    uint32_t filas = 0;
    uint32_t columnas = 0;
    const size_t SIZE_OF_UINT32 = 4;
    socket.receive((char *) &filas, SIZE_OF_UINT32);
    filas = ntohl(filas);
    socket.receive((char *) &columnas, SIZE_OF_UINT32);
    columnas = ntohl(columnas);
    // std::cout << "recibi filas: " << filas << std::endl;
    // std::cout << "recibi columnas: " << columnas << std::endl;

    for(size_t i = 0; i < filas ; i++){
        std::vector<int> aux;
        // std::cout << "recibe vector" << std::endl;
        for(size_t i = 0; i < columnas ; i++){
            uint32_t num;
            socket.receive((char*) &num, sizeof(uint32_t));
            num = ntohl(num);
            // std::cout << num;
            aux.push_back(num);
        }
        // std::cout << std::endl;
        lvl2.push_back(aux);
        // std::cout << "recibi vector" << std::endl;
        // std::cout << "hice pritn de vector" << std::endl;
    }
    // printVector(lvl2);
    std::cout << "ya receibi el mapa" << std::endl;
    inMatch = true;
}

// Se usa al finalizar el ingreso de input
void ClientReceiver::stop(){
    socket.shutdown_read();
    is_running = false;
}

void ClientReceiver::isAtMenu(){
    atMenus = true;
}

bool ClientReceiver::isInMatch(){
    return inMatch;
}

void ClientReceiver::quitMatch(){
    inMatch = false;
}

