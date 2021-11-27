#include "connection.h"
#include <vector>

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");// Поддержка кириллицы в консоли Windows
    sf::TcpListener listener;

    if(listener.listen(3000) != sf::Socket::Done) {
        std::cerr << "Error";
    }

    std::vector<sf::TcpSocket> sockets(2);
    for (auto &elem : sockets) {
        listener.accept(elem);
    }

    sf::Packet packet;
    packet << "Hi, i'm server";

    for (auto &elem : sockets) {
        elem.send(packet);
    }

    return 0;
}