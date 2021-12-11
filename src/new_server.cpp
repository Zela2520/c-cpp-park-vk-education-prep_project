#include "../include/connection.h"

int main(int argc, char* argv[]) {
    server_logic::Server my_server(3000);
    my_server.start_connection();
    my_server.receive_clients();
    my_server.clients_init();
    my_server.send_data();
    my_server.start_server();
    return 0;
}
