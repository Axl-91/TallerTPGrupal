#ifndef SOCKETCLOSED__H
#define SOCKETCLOSED__H

#include <typeinfo>
#include <string>
#include <errno.h>
class SocketClosed : public std::exception {
public:
    explicit SocketClosed(const std::string& msg):
        _errno(errno),
        error_msg(msg)
    {
        error_msg += "\nstrerror(errno): ";
        error_msg += std::string(strerror(_errno));
    }

    virtual ~SocketClosed() noexcept {}

    virtual const char *what() const noexcept{
        return this->error_msg.c_str();
    }
private:
    int _errno;
    std::string error_msg;
};

#endif
