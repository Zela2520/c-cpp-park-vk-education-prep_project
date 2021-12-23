#include "../../include/danya_server.h"

int main(int argc, char* argv[]) {
    Server my_server(3000);
    my_server.sendData();
    my_server.start_server();
    return 0;
}

