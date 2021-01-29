#ifndef ACCEPTORCLOSED__H
#define ACCEPTORCLOSED__H

#include <typeinfo>
#include <string>
class AcceptorClosed : public std::exception {
public:
    explicit AcceptorClosed(const std::string &error_msg){
        _error_msg += error_msg;
    }
    virtual ~AcceptorClosed() noexcept {}
    virtual const char *what() const noexcept {
        return _error_msg.c_str();
    }
private:
    std::string _error_msg;
};

#endif
