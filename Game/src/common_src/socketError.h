#ifndef SOCKETERROR__H
#define SOCKETERROR__H

#include <typeinfo>
#include <string>
#include <errno.h>
class SocketError : public std::exception {
public:
    explicit SocketError(const std::string& msg):
        _errno(errno),
        error_msg(msg)
    {
        error_msg += "\nstrerror(errno): ";
        error_msg += std::string(strerror(_errno));
    }

    virtual ~SocketError() noexcept {}

    virtual const char *what() const noexcept{
        return this->error_msg.c_str();
    }
private:
    int _errno;
    std::string error_msg;
};

#endif
