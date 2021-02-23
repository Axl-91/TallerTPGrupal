#ifndef THACCEPTOR__T
#define ThACCEPTOR__T

#include "../common_src/socket.h"
#include "../common_src/thread.h"
#include "user.h"
#include "menuHandler.h"
#include <vector>
#include <utility>
#include <atomic>

class ThAcceptor : public Thread{
public:
    ThAcceptor(const char *service, MenuHandler& mH);
    Socket accept();
    void stop_accepting();
    virtual void run() override;
    void operator()();

private:
    Socket acceptor_socket;
    std::atomic<bool> keep_accepting;
    MenuHandler &menuHandler;
};

#endif
