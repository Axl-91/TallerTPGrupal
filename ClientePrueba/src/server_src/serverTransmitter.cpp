#include "serverTransmitter.h"

ServerTransmitter::ServerTransmitter(Socket &socket):
    socket(socket)
{}

ServerTransmitter::ServerTransmitter(ServerTransmitter&& other):
    socket(other.socket)
{}
    // ~Transmitter(){}
void ServerTransmitter::sendTag(update_tag_t &aTag){
    std::unique_lock<std::mutex> lock(m);

    socket.send((char*) &aTag, sizeof(update_tag_t));   
}

void ServerTransmitter::sendString(std::string &aString){
    std::stringstream aux(aString);

    std::unique_lock<std::mutex> lock(m);

    uint32_t length = aux.str().length();
    const size_t SIZE_OF_UINT32 = 4;
    length = htonl(length);
    socket.send((char *) &length, SIZE_OF_UINT32);
    socket.send(aux.str().data(), aux.str().length());   
}

// void printVector(std::vector<std::vector<uint32_t>> lvl1){
//     for(auto v:lvl1){
//         for(auto num:v)
//             std::cout << num;
//         std::cout << std::endl;
//     }
// }

void ServerTransmitter::sendMap(std::vector<std::vector<int>> &lvl1){
    // printVector(lvl1);
    uint32_t filas = lvl1.size();
    filas = htonl(filas);
    uint32_t columnas = lvl1[0].size();
    columnas = htonl(columnas);

    std::unique_lock<std::mutex> lock(m);

    const size_t SIZE_OF_UINT32 = 4;
    socket.send((char *) &filas, SIZE_OF_UINT32);
    socket.send((char *) &columnas, SIZE_OF_UINT32);

    for(auto v:lvl1){
        for(auto celda:v){
            // std::cout << celda;
            celda = htonl(celda);
            socket.send((char *) &celda, SIZE_OF_UINT32);
        }
    }
}

void ServerTransmitter::sendPlayer(Player_t &player){
    std::unique_lock<std::mutex> lock(m);

    socket.send((char *) &player, sizeof(Player_t));
}


void ServerTransmitter::sendMapUpdate(Map_change_t &aMapChange){
    std::unique_lock<std::mutex> lock(m);
    socket.send((char*) &aMapChange, sizeof(Map_change_t));
}

void ServerTransmitter::sendPlayerID(size_t &ID){
   std::unique_lock<std::mutex> lock(m);

    socket.send((char*) &ID, sizeof(ID));
}
