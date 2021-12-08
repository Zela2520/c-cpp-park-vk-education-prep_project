#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace sf;

//struct Ball {
//    int x;
//    int y;
//    std::string color;
//};

class Object {
    Sprite sprite;
protected:
    int x = 0;
    int y = 0;
public:
//    Object(int _x, int _y) {
//        x = _x;
//        y = _y;
//    }
    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    void setX(int _x) {
        x = _x;
    }
    void setY(int _y) {
        y = _y;
    }
    void goUp(int distance = 1) {
        y-= distance;
    }
    void goDown(int distance = 1) {
        y += distance;
    }
    void goRight(int distance = 1) {
        x += distance;
    }
    void goLeft(int distance = 1) {
        x -= distance;
    }
};

class Ball : public Object {
//    Color color;
    float size;
public:
    Ball(int _x, int _y, Color _color, float _size) {
        x = _x;
        y = _y;
//        color = _color;
        size = _size;
    }
//    Color getColor() const {
//        return color;
//    }
//    Color setColor(sf::Color _color) const {
//        color = _color;
//    }
friend sf::Packet& operator >> (sf::Packet& packet, Ball& ball);
    friend sf::Packet& operator << (sf::Packet& packet, const Ball& ball);
};

sf::Packet& operator << (sf::Packet& packet, const Ball& ball) {
    return packet << ball.x << ball.y;
}
//
sf::Packet& operator >> (sf::Packet& packet, Ball& ball) {
    return packet >> ball.x >> ball.y;
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
    std::vector<Ball> balls(clients.size(), Ball(0, 0, sf::Color::Black, 15));  // инициализируем клиентов значниями по умолчанию.
    // Заранее отправляем клиентам данные о том, что мячи расположены на нулевых координатах.
    for (auto & client : clients) {  // Для каждого клиента.
        for (auto & ball : balls) {  // О каждом шаре.
            packet << ball;
            client.send(packet);
            packet.clear();
            
            std::cout << ball.getX() << ' '<< ball.getY() << '\n';  // Дебаг
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
                balls[i].goUp();
            }
            if (dir == "RIGHT") {
                balls[i].goRight();
            }
            if (dir == "DOWN") {
                balls[i].goDown();
            }
            if (dir == "LEFT") {
                balls[i].goLeft();
            }
        }

        // отправляем обновлённые данные об изменение всех объектов на сервере каждому клиенту
        for (int i = 0; i < clients.size(); ++i) {
            for (int j = 0; j < balls.size(); ++j) {
                packet << balls[j];
                clients[i].send(packet);
                packet.clear();
                std::cout << balls[j].getX() << ' '<< balls[j].getY() << '\n';
            }
        }
    }
    return 0;
}