#ifndef SOCKET__T
#define SOCKET__T


#define ERROR 1

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <errno.h>
#include <utility>
#include "acceptorClosed.h"
#include "socketError.h"
#include "socketClosed.h"
class Socket{
public:
    Socket();
    ~Socket();
    Socket(Socket&& socket);
    void shutdown_read();
    void shutdown_writing();
    void bind_and_listen(const char *service);
    Socket accept();
    void connect(const char *host_name, const char *service);
    void send(const char *buffer, size_t buf_l);
    void receive(char *buffer, size_t buf_l);
    bool isConnected();
private:
    explicit Socket(int fd);
    int fd;
};

#endif
