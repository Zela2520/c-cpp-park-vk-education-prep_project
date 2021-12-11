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
    if (argc != 2) {
        perror("The server haven't been init");
        exit(EXIT_FAILURE);
    }

    sf::TcpListener listener;
    // std::thread th();

    // устанвливаем по какому порту  будет проходить подключение к серверу
    if (listener.listen(3000) != sf::Socket::Done) {
        std::cerr << "Error";
    }

    // сделать очередь для ожидание на подключения к серверу
    // рассмотрим случай для двух клиентов
    std::vector<sf::TcpSocket> clients(4);


    // инициализация сокета для дальнейшего взаимодействия с клиентом
    // если кто-то подключается, то accept индентифицирует клиента для дальнешей работы с ним
    for (auto &socket : clients) {
        listener.accept(socket);
    }

    // Для передачи даннных между клиент сервером создаём пакет, который будет летать по сети
    sf::Packet packet;

    // инициализируем клиентов значниями по умолчанию
    std::vector<Ball> user_balls(clients.size(),{0,0, "Black"});

    // записывем данные о каждом мяче на карте в пакет и отправляем каждому клиенту все мячи
    for (int i = 0; i < clients.size(); ++i) {
        // std::thread th(sent_game(packet), packet);
        for (int j = 0; j < user_balls.size(); ++j) {
            packet << user_balls[j];
            clients[i].send(packet);
            packet.clear();

            // печатаем мячики, которые отправляются каждому клиенту
            std::cout << user_balls[j].x << ' '<< user_balls[j].y << ' ' << user_balls[j].color << '\n';
        }
    }

    while(1) {
        // получаем пакет с информацией о перемещение каждого клиента и извлекаем информацию о перемещение каждого клиента
        // перемещение i-ого клиента значит перемещение i-ого мячика
        for (int i = 0; i < clients.size(); ++i) {// проблема в этом цикле - все мячи смещаются на одно и тоже расстояние одновременно
            // указывем направление движения объекта
            std::string dir = "\0";
            clients[i].receive(packet);
            packet >> dir;
            packet.clear();
            std::cout << dir << "\n";

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
        }

        // отправляем обновлённые данные об изменение всех объектов на сервере каждому клиенту
        for (int i = 0; i < clients.size(); ++i) {
            for (int j = 0; j < user_balls.size(); ++j) {
                packet << user_balls[j];
                clients[i].send(packet);
                packet.clear();
                std::cout << user_balls[j].x << ' '<< user_balls[j].y << ' ' << user_balls[j].color << '\n';
            }
        }
    }
    return 0;
}