#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;

//struct Object {
//    int x;
//    int y;
//    std::string color;
//};

class Object {
protected:
    Sprite sprite;
    Texture texture;
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
};

class Unmovable : public Object {
public:
    Unmovable(int _x, int _y, Sprite _sprite) {
        x = _x;
        y = _y;
        sprite = _sprite;
    }
    void draw(RenderWindow& window) {
        sprite.setPosition(x, y);
        window.draw(sprite);
    }
    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable);
};

class Player : public Object {
    float size;
public:
    Player(int _x, int _y, Color _color, float _size) {
        x = _x;
        y = _y;
//        color = _color;
        size = _size;
    }
    void draw(RenderWindow& window) {
        sf:CircleShape circle;
        circle.setRadius(15.f);
        circle.setFillColor(Color::Black);
        circle.setPosition(x, y);
        window.draw(circle);
    }
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
};

sf::Packet& operator << (sf::Packet& packet, const bool* directions) {  // Запись в пакет направлений движения.
    return packet << directions[0] << directions[1] << directions[2] << directions[3];
}
sf::Packet& operator >> (sf::Packet& packet, Player& player) {
    return packet >> player.x >> player.y;
}
sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable) {
    return packet >> unmovable.x >> unmovable.y;
}



int main() {
    setlocale(LC_ALL, "");
    
    sf::TcpSocket socket;  // Создаем сокет. У каждого клиента - свой сокет.
    socket.connect("127.0.0.1", 3000);  // Подключаемся к серверу по заданному порту.
    
    sf::Packet packet;  // Создаём пакет для общения клиента с сервером.
    std::vector<Player> players(2, Player(0, 0, sf::Color::Black, 15));  // Инициализируем начальное положение объектов на карте, принимая данные от сервера.

    sf::Texture gachiTexture;
    gachiTexture.loadFromFile("/home/dima/!Stuff/TP/trying to make engine/baby.png");
    Sprite gachiSprite(gachiTexture);
    std::vector<Unmovable> unmovables(1, Unmovable(200, 200, gachiSprite));
//    Ball ball(0, 0, sf::Color::Black, 15);
//    players.push_back(ball);

    sf::RenderWindow window(sf::VideoMode(500, 500), "Squid game");  // Создаём игровое окно.

//    if (typeid(objects[2]).name() == typeid(Object).name()) {std::cout << "JOPA"; return 1;}
    while (window.isOpen()) {
        // Получение информации обо всех шарах.
        sf::CircleShape circle;
        for (auto &player : players) {  // Пробегаем по всем шарам. На 1 шар 1 пакет.
            socket.receive(packet);  // Получаем пакет.
            packet >> player;  // Записываем данные из пакета в текущую структуру шара.
            packet.clear();

            std::cout << player.getX() << ' ' << player.getY() << ' ';  // Дебаг.
        }
        // Отрисовка всех шаров.
        window.clear(sf::Color::White);
        for (auto &player : players) {
            player.draw(window);
        }
        for (auto &unmovable : unmovables) {  // Пробегаем по всем шарам. На 1 шар 1 пакет.
            socket.receive(packet);  // Получаем пакет.
            packet >> unmovable;  // Записываем данные из пакета в текущую структуру шара.
            packet.clear();

            std::cout << unmovable.getX() << ' ' << unmovable.getY() << ' ';  // Дебаг.
        }
        for (auto& unmovable : unmovables) {
            unmovable.draw(window);
        }
        window.display();


        sf::Event event{}; // переменная для отслеживания событий, происходящих на кажой итерации цикла
        bool directions[4] = {false, false, false, false};  // направление движения, которое будет обрабатваться на сервере
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                directions[0] = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                directions[1] = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                directions[2] = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                directions[3] = true;
            }
        }

        // Запаковываем данные пользователя в пакет и отправляем на сервер
        packet << directions;
        socket.send(packet);
        packet.clear();
//        std::cout << directions << '\n';  // Дебаг
    }
    return 0;
}