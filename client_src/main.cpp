#include "client.h"

int main(int argc, char* argv[]){
    try {
        Client client(argv[1], argv[2]);
        client.run();
    } catch (const std::exception &e){
        std::cerr << "Excepción en client.run();" << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (...) { // ellipsis: catch anything
        printf("Unknown error!");
    }

    return 0;
}
