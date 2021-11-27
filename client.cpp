#include "connection.h"

int main() {
    setlocale(LC_ALL, "");
    sf::TcpSocket socket;
    socket.connect("127.0.0.1", 3000);
    sf::Packet packet;
    socket.receive(packet);
    char data[100] = "";
    packet >> data;
    std::cout << data;
    return 0;
}