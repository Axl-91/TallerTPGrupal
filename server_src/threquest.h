#ifndef THREQUEST__T
#define THREQUEST__T
#include <map>
#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "../common_src/receiver.h"
#include "../common_src/transmitter.h"
// #include "protectedResources.h"
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>
#include <atomic>

class ThRequest : public Thread{
private:
    Socket s;
    std::atomic<bool> is_running;
    
public:
    // ThRequest(ProtectedResources& resources, Socket socket);
    ThRequest(Socket socket);
    ~ThRequest();
    void operator()();
    virtual void run() override;

            // Recibe una peticion por un recurso
            // busca en el recursos map
            // Si no lo encuentra tiene que devolver algun error

    bool is_dead();
    void receive_petition(std::stringstream& petition);
    void send_response(std::stringstream& buf);
};

#endif
