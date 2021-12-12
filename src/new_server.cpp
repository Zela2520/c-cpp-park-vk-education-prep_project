#include "../include/connection.h"

int main(int argc, char* argv[]) {
    server_logic::Server my_server(3000);
    my_server.set_connection();
    my_server.receive_clients();
    std::cout << "Данные клиента полученые\n";
    my_server.clients_init();
    my_server.send_data();
    my_server.start_server();
    return 0;
}
