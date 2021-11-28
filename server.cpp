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

    // рассмотрим случай для двух клиентов
    std::vector<sf::TcpSocket> clients(2);

    // инициализация сокета для дальнейшего взаимодействия с клиентом
    // если кто-то подключается, то accept индентифицирует клиента для дальнешей работы с ним
    for (auto &socket : clients) {
        listener.accept(socket);
    }

    // Для передачи даннных между клиент сервером создаём пакет, который будет летать по сети
    sf::Packet packet;

    // инициализируем клиентов значниями по умолчанию
    std::vector<Ball> user_balls(clients.size(),{0,0, "Black"});

    // записывем данные в пакет и отправляем
    for (int i = 0; i < clients.size(); ++i) {
        for (int j = 0; j < user_balls.size(); ++j) {
            packet << user_balls[j];
            clients[j].send(packet);
            packet.clear();
        }
    }
    /*packet << user_ball;
    client.send(packet);
    // чистим пакет после отправки
    packet.clear();

    packet << user_ball_2;
    client_2.send(packet);
    // чистим пакет после отправки
    packet.clear();*/

    while(1) {
        // укащывем направление движения объекта
        std::string dir;

        // получаем пакет и извлекаем информацию
        for (int i = 0; i < clients.size(); ++i) {
            clients[i].receive(packet);
            packet >> dir;
            packet.clear();

            // обрабатываем действие пользователя
            if (dir == "UP") {
                --user_balls[i].y;
            }
            if (dir == "RIGHT") {
                ++user_balls[i].x;
            }
            if (dir == "DOWN") {
                ++user_balls[i].y;
            }
            if (dir == "LEFT") {
                --user_balls[i].x;
            }

            // отправляем обновлённые данные об объекте на сервер
            /*packet << user_balls[i];
            clients[i].send(packet);
            packet.clear();*/
        }
        for (int i = 0; i < clients.size(); ++i) {
            for (int j = 0; j < user_balls.size(); ++j) {
                packet << user_balls[j];
                clients[i].send(packet);
                packet.clear();
            }
        }
    }
    return 0;
}