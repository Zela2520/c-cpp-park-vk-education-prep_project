#include "connection.h"
#include <vector>

struct Ball {
    int x;
    int y;
    std::string color;
};

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");// Поддержка кириллицы в консоли Windows
    sf::TcpListener listener;

    if (listener.listen(3000) != sf::Socket::Done) {
        std::cerr << "Error";
    }

    std::vector<sf::TcpSocket> sockets(2);
    for (auto &elem : sockets) {
        listener.accept(elem);
    }

    sf::Packet packet;  // Пакет.
    std::vector<Ball> balls(sockets.size(), {0, 0, "Black"});  // Массив шаров.


    for (int i = 0; i < sockets.size(); ++i) {   //  Инициализируем нулями все шары.
        for (int j = 0; j < balls.size(); ++j) {
            packet << balls[j].x << balls[j].x  << balls[j].color;
        }
        sockets[i].send(packet);
        packet.clear();
    }

    while (true) {
        for (int i = 0; i < sockets.size(); ++i) {   //  Получаем направление смещения шаров.
            sockets[i].receive(packet);
            std::string dir;
            packet >> dir;  // Получаем направление смещения.
            if (dir == "UP") --balls[i].y;
            if (dir == "RIGHT") ++balls[i].x;
            if (dir == "DOWN") ++balls[i].y;
            if (dir == "LEFT") --balls[i].x;
            packet.clear();
        }

        for (int i = 0; i < sockets.size(); ++i) {   //  Рассылаем пакеты с данными.
            for (int j = 0; j < sockets.size(); ++j) {
                packet << balls[j].x << balls[j].y << balls[j].color;
            }
            sockets[i].send(packet);
            packet.clear();
        }
    }


    return 0;
}