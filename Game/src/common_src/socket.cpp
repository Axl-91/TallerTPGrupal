#include "socket.h"

Socket::Socket(){
    fd = -1;
}
Socket::~Socket(){
    if (fd != -1)
        close(fd);
    fd = -1;
}
Socket::Socket(Socket&& socket): fd(socket.fd) {
    socket.fd = -1;
}
Socket::Socket(int fd): fd(fd) {}

void Socket::shutdown_read(){
    shutdown(fd, SHUT_RD);
}
void Socket::shutdown_writing(){
    shutdown(fd, SHUT_WR);
}

bool Socket::isConnected(){
    if(fd == -1)
        return false;
    return true;
}

void Socket::bind_and_listen(const char *service){
    struct addrinfo hints, *results, *rp;
    int status = 0;
    hints.ai_family = AF_INET;    
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;
    int val = 1;

    status = getaddrinfo(0, service, &hints, &results);  
    if (status != 0) { 
        throw SocketError("Error en socket.bin_and_listen().");
    }
    for (rp = results; rp != NULL; rp = rp->ai_next){
        fd = ::socket(AF_INET, SOCK_STREAM, 0);
        int s = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        if (s == -1) {
            close(fd);
            fd = -1;
            throw SocketError("Error en socket.bin_and_listen().");
        }
        if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0){
            break;               
        }
        close(fd);
        fd = -1;
    }
    freeaddrinfo(results); // libero lista de direcciones
    if (listen(fd, 10) == -1){ 
        close(fd);
        fd = -1;
        throw SocketError("Error en socket.bin_and_listen().");
    }
}

Socket Socket::accept(){
    int accepted_fd = 0;
    accepted_fd = ::accept(fd, NULL, NULL);
    if (accepted_fd == -1){
        if (errno == 22)
            throw AcceptorClosed("Se cerró el socket aceptador.");
        else
            throw SocketError("Error en socket.accept().");
    }
    return std::move(Socket(accepted_fd));
}

void Socket::connect(const char *host_name, const char *service){
    struct addrinfo hints, *result, *rp;
    int skt = 0;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_protocol = 0;
    hints.ai_flags = 0;
    skt = getaddrinfo(host_name, service, &hints, &result);

    if (skt != 0) {
        close(fd);
        fd = -1;
        throw SocketError("Error en socket.connect().");
    }
    for (rp = result; rp != NULL; rp = rp->ai_next){
        fd = ::socket(AF_INET, SOCK_STREAM, 0);
        if (::connect(fd, rp->ai_addr, rp->ai_addrlen) == 0){      
            break; 
        }  
        close(fd);
        fd = -1;
    }
    if (rp == NULL){              
        throw SocketError("Error en socket.connect().");
    }
    freeaddrinfo(result); 
}

void Socket::send(const char *buffer, size_t buf_l){
    size_t bytes_sent;
    bytes_sent = 0;

    while (bytes_sent < buf_l){
        int s = 0;
        s = ::send(fd, &buffer[bytes_sent], buf_l - bytes_sent, MSG_NOSIGNAL);
        if (s <= 0){ 
            throw SocketError("Error en socket.receive()");
        }
        bytes_sent += s;
    }
}
 
void Socket::receive(char *buffer, size_t buf_l){
    size_t bytes_recv = 0;

    while (bytes_recv < buf_l){
        int r = 0;
        r = ::recv(fd, &buffer[bytes_recv], buf_l - bytes_recv, 0);
        if (r < 0){
            throw SocketError("Error en socket.receive()");
        }else if (r == 0){
            throw SocketClosed("Se cerro el socket.");
            break;
        }else{
            bytes_recv += r;
        }
    }
}
