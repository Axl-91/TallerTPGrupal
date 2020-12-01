#ifndef THACCEPTOR__T
#define ThACCEPTOR__T

#include "../common_src/socket.h"
#include "threquest.h"
#include "../common_src/thread.h"
#include <map>
#include <vector>
#include <utility>
#include <atomic>

class ThAcceptor : public Thread{
public:
    // ThAcceptor(const char *service, 
    //     ProtectedResources &resources);
    ThAcceptor(const char *service);
    Socket accept();
    void stop_accepting();
    // void process_requests();
    virtual void run() override;
    void operator()();

private:
    Socket acceptor_socket;
    std::atomic<bool> keep_accepting;
    std::vector<ThRequest*> threads;
    // ProtectedResources& resources;      
    void delete_finish_clients(std::vector<ThRequest*> &threads);

    void bind_and_listen(const char *service);
};


#endif
