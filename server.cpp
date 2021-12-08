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
    // Устанавливаем по какому порту будет проходить подключение к серверу
    if (listener.listen(3000) != sf::Socket::Done) {  // Слушаем порт 3000.
        std::cerr << "Error";
    }
    // Рассмотрим случай для двух клиентов
    std::vector<sf::TcpSocket> clients(2);
    // если кто-то подключается, то accept индентифицирует клиента для дальнешей работы с ним
    for (auto &socket : clients) {
        listener.accept(socket);
    }


    sf::Packet packet;  // Для передачи даннных между клиент сервером создаём пакет, который будет летать по сети.
    std::vector<Ball> balls(clients.size(),{0,0, "Black"}); // инициализируем клиентов значниями по умолчанию.
    // Заранее отправляем клиентам данные о том, что мячи расположены на нулевых координатах
    for (auto & client : clients) {  // Для каждого клиента.
        for (auto & ball : balls) {  // О каждом шаре.
            packet << ball;
            client.send(packet);
            packet.clear();
            
            std::cout << ball.x << ' '<< ball.y << ' ' << ball.color << '\n';  // Дебаг
        }
    }

    while (true) {
        // получаем пакет с информацией о перемещении какждого клиента и извлекаем информацию о перемещение каждого клиента
        // перемещение i-ого клиента значит перемещение i-ого мячика
        for (int i = 0; i < clients.size(); ++i) {
            // указывем направление движения объекта
            clients[i].receive(packet);
            std::string dir;
            packet >> dir;
            packet.clear();
            std::cout << dir << "\n";  // Дебаг.

            // обрабатываем действие пользователя
            if (dir == "UP") {
                --balls[i].y;
            }
            if (dir == "RIGHT") {
                ++balls[i].x;
            }
            if (dir == "DOWN") {
                ++balls[i].y;
            }
            if (dir == "LEFT") {
                --balls[i].x;
            }
        }

        // отправляем обновлённые данные об изменение всех объектов на сервере каждому клиенту
        for (int i = 0; i < clients.size(); ++i) {
            for (int j = 0; j < balls.size(); ++j) {
                packet << balls[j];
                clients[i].send(packet);
                packet.clear();
                std::cout << balls[j].x << ' '<< balls[j].y << ' ' << balls[j].color << '\n';
            }
        }
    }
    return 0;
}