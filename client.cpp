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
    void draw(sf::RenderWindow& window) {
        sf::CircleShape circle;
        circle.setPosition(x, y);
        circle.setRadius(size);
        circle.setFillColor(sf::Color::Black);
        window.draw(circle);
    }
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



int main() {
    setlocale(LC_ALL, "");
    
    sf::TcpSocket socket;  // Создаем сокет. У каждого клиента - свой сокет.
    socket.connect("127.0.0.1", 3000);  // Подключаемся к серверу по заданному порту.
    
    sf::Packet packet;  // Создаём пакет для общения клиента с сервером.
    std::vector<Ball> balls(2, Ball(0, 0, sf::Color::Black, 15));  // Инициализируем начальное положение объектов на карте, принимая данные от сервера.

    sf::RenderWindow window(sf::VideoMode(500, 500), "Squid game");  // Создаём игровое окно.


    while (window.isOpen()) {
        // Получение информации обо всех шарах.
        sf::CircleShape circle;
        for (auto &ball : balls) {  // Пробегаем по всем шарам. На 1 шар 1 пакет.
            socket.receive(packet);  // Получаем пакет.
            packet >> ball;  // Записываем данные из пакета в текущую структуру шара.
            packet.clear();

            std::cout << ball.getX() << ' ' << ball.getY() << ' ';  // Дебаг.
        }

        // Отрисовка всех шаров.
        window.clear(sf::Color::White);
        for (auto &ball : balls) {
            ball.draw(window);
        }
        window.display();


        sf::Event event{}; // переменная для отслеживания событий, происходящих на кажой итерации цикла
        std::string dir;  // направление движения, которое будет обрабатваться на сервере
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                dir = "UP";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                dir = "DOWN";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                dir = "RIGHT";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                dir = "LEFT";
            }
        }

        // Запаковываем данные пользователя в пакет и отправляем на сервер
        packet << dir;
        socket.send(packet);
        packet.clear();
        std::cout << dir << '\n';  // Дебаг
    }
    return 0;
}