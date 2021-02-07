#include "serverTransmitter.h"

ServerTransmitter::ServerTransmitter(Socket &socket):
    socket(socket)
{}

ServerTransmitter::ServerTransmitter(ServerTransmitter&& other):
    socket(other.socket)
{}
    // ~Transmitter(){}
void ServerTransmitter::sendTag(update_tag_t &aTag){
    socket.send((char*) &aTag, sizeof(update_tag_t));   
}

void ServerTransmitter::sendString(std::string &aString){
    std::stringstream aux(aString);
    uint32_t length = aux.str().length();
    const size_t SIZE_OF_UINT32 = 4;
	std::cout << "envio largo: " << length << std::endl;
    length = htonl(length);
    socket.send((char *) &length, SIZE_OF_UINT32);
	std::cout << "envio string: " << aString << std::endl;
    socket.send(aux.str().data(), aux.str().length());   
}

void printVector(std::vector<std::vector<uint32_t>> lvl1){
    for(auto v:lvl1){
        for(auto num:v)
            std::cout << num;
        std::cout << std::endl;
    }
}

void ServerTransmitter::sendMap(std::vector<std::vector<int>> &lvl1){
    // printVector(lvl1);
    uint32_t filas = lvl1.size();
    filas = htonl(filas);
    uint32_t columnas = lvl1[0].size();
    columnas = htonl(columnas);
    const size_t SIZE_OF_UINT32 = 4;
    std::cout << "voy a enviar filas" << std::endl;
    socket.send((char *) &filas, SIZE_OF_UINT32);
    std::cout << "voy a enviar columnas" << std::endl;
    socket.send((char *) &columnas, SIZE_OF_UINT32);

    std::cout << "voy a enviar mapa" << std::endl;
    for(auto v:lvl1){
        for(auto celda:v){
            std::cout << celda;
            celda = htonl(celda);
            socket.send((char *) &celda, SIZE_OF_UINT32);
        }
    }
    std::cout << "termine de enviar mapa" << std::endl;
}

void ServerTransmitter::sendPlayer(Player_t &player){
    // std::cout << "voy a enviar playerInfo: \n player.x:" << player.x << "\t player.y:" << player.y << std::endl;
    // std::cout<< player.health<<std::endl;
    socket.send((char *) &player, sizeof(Player_t));
}


void ServerTransmitter::sendMapUpdate(Map_change_t &aMapChange){
    // std::cout <<"chichiwolen "<< aMapChange.x<< std::endl;
    // std::cout << aMapChange.y << std::endl;
    
    // std::cout << aMapChange.value << std::endl;
    
    socket.send((char*) &aMapChange, sizeof(Map_change_t));
}

void ServerTransmitter::sendPlayerID(size_t &ID){
    socket.send((char*) &ID, sizeof(ID));
}
