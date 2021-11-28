#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>

struct Ball {
    int x;
    int y;
    std::string color;
};

sf::Packet& operator <<(sf::Packet& packet, const Ball& ball)
{
    return packet << ball.x << ball.y << ball.color;
}

sf::Packet& operator >>(sf::Packet& packet, Ball& ball)
{
    return packet >> ball.x >> ball.y >> ball.color;
}

int main(int argc, char* argv[]) {
    sf::TcpListener listener;

    // устанвливаем по какому порту  будет проходить подключение к серверу
    if (listener.listen(3000) != sf::Socket::Done) {
        std::cerr << "Error";
    }

    // рассмотрим случай с одним клиентом
    sf::TcpSocket client;

    // инициализация сокета для дальнейшего взаимодействия с клиентом
    // если кто-то подключается, то accept индентифицирует клиента для дальнешей работы с ним
    listener.accept(client);

    // Для передачи даннных между клиент сервером создаём пакет, который будет летать по сети
    sf::Packet packet;

    // инициализируем клиента значниями по умолчанию
    Ball user_ball{0,0, "Black"};

    // записывем данные в пакет и отправляем
    packet << user_ball;
    client.send(packet);

    // чистим пакет после отправки
    packet.clear();

    while(1) {
        // укащывем направление движения объекта
        std::string dir;

        // получаем пакет и извлекаем информацию
        client.receive(packet);
        packet >> dir;
        packet.clear();

        // обрабатываем действие пользователя
        if (dir == "UP") {
            --user_ball.y;
        }
        if (dir == "RIGHT") {
            ++user_ball.x;
        }
        if (dir == "DOWN") {
            ++user_ball.y;
        }
        if (dir == "LEFT") {
            --user_ball.x;
        }

        // отправляем обновлённые данные об объекте на сервер
        packet << user_ball;
        client.send(packet);
        packet.clear();
    }
    return 0;
}