#include "clientReceiver.h"

ClientReceiver::ClientReceiver(Socket &socket, 
    std::vector<std::vector<int>> &m, 
    ProtectedUpdateQueue &q):
    socket(socket),
    is_running(false),
    inMatch(false),
    map(m),
    matchEnded(false),
    uQ(q)
{}

// ClientReceiver::ClientReceiver(ClientReceiver&& other):
//     socket(other.socket),
//     lvl2(other.lvl2),
//     player(other.player),
//     mapChange(other.mapChange)
// {}
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

void ClientReceiver::receiveGame(){
    Update_t anUpdate;
    anUpdate.mapChangeAvailable = false;
    uint32_t length = 0;
    const size_t SIZE_OF_UINT32 = 4;
    update_tag_t aTag = TAG_NO_UPDATE;
    // socket.receive((char *) &length, SIZE_OF_UINT32);
    // length = ntohl(length);
    // if(length == 0){
    //     is_running = false;
    // }
    // std::vector<char> buffer(length+1, 0);
    // socket.receive(buffer.data(), length);
    // std::string response = buffer.data();
    socket.receive((char*) &aTag, sizeof(update_tag_t));
    // std::cout << "ClientReceiver(), recibo mensaje: \n" << response << std::endl;

    if(aTag == TAG_MAP_INIT){
     std::cout<<"client.receive cargo el mapa"<<std::endl;
        receiveMap();
    }
    if(aTag == TAG_PLAYER_INFO){
        receivePlayerInfo(anUpdate);
        uQ.push(anUpdate);
    }
    if(aTag == TAG_MAP_CHANGE){
        receiveMapChange(anUpdate);
        anUpdate.mapChangeAvailable = true;
        uQ.push(anUpdate);
    }

    if(aTag == TAG_GAME_QUIT){
        matchEnded = true;
    }
}

void ClientReceiver::receivePlayerInfo(Update_t &anUpdate){
    Player_t aux;
    socket.receive((char *) &aux, sizeof(Player_t));
    anUpdate.playerUpdate = aux;
}

void ClientReceiver::receiveMapChange(Update_t &anUpdate){
    Map_change_t aux;
    socket.receive((char *) &aux, sizeof(Map_change_t));
    anUpdate.mapChange = aux;
    anUpdate.mapChangeAvailable = true;
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
    uint32_t filas = 0;
    uint32_t columnas = 0;
    const size_t SIZE_OF_UINT32 = 4;
    socket.receive((char *) &filas, SIZE_OF_UINT32);
    filas = ntohl(filas);
    socket.receive((char *) &columnas, SIZE_OF_UINT32);
    columnas = ntohl(columnas);

    for(size_t i = 0; i < filas ; i++){
        std::vector<int> aux;
        for(size_t i = 0; i < columnas ; i++){
            uint32_t num;
            socket.receive((char*) &num, sizeof(uint32_t));
            num = ntohl(num);
            aux.push_back(num);
        }
        map.push_back(aux);
    }
    inMatch = true;
}

// Se usa al finalizar el ingreso de input
void ClientReceiver::stop(){
    socket.shutdown_read();
    is_running = false;
}

bool ClientReceiver::isInMatch(){
    return inMatch;
}

void ClientReceiver::quitMatch(){
    inMatch = false;
}
