#include "../../include/danya_server.h"

int main(int argc, char* argv[]) {
    Server my_server(3000);
//    my_server.set_connection();
//    my_server.receive_clients();
    my_server.sendData();
    my_server.start_server();
    return 0;
}

