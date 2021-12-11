#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "model.h"

using namespace sf;

//struct Object {
//    int x;
//    int y;
//    std::string color;
//};
//
//class Object {
//protected:
//    Sprite sprite;
//public:
////    explicit Object(const Texture& texture) {
////        sprite = new Sprite(texture);
////    }
//    float getX() const {
//        return sprite.getPosition().x;
//    }
//    float getY() const {
//        return sprite.getPosition().y;
//    }
//    void setX(float _x) {
//        sprite.setPosition(_x, this->getY());
//    }
//    void setY(float _y) {
//        sprite.setPosition(this->getX(), _y);
//    }
//    void goUp(float distance = 1) {
//        sprite.move(0, -distance);
//    }
//    void goDown(float distance = 1) {
//        sprite.move(0, distance);
//    }
//    void goRight(float distance = 1) {
//        sprite.move(distance, 0);
//    }
//    void goLeft(float distance = 1) {
//        sprite.move(-distance, 0);
//    }
//    void draw(RenderWindow& window) {
////        std::cout << "Нарисовался" << std::endl;
//        window.draw(sprite);
////        window.display();
//    }
//};
//
////class Ball : public Object {
//////    Color color;
////    float size;
////public:
////    Ball(float _x, float _y, Color _color, float _size) {
////        x = _x;
////        y = _y;
//////        color = _color;
////        size = _size;
////    }
//////    Color getColor() const {
//////        return color;
//////    }
//////    Color setColor(sf::Color _color) const {
//////        color = _color;
//////    }
////};
//
//class Unmovable : public Object {
//private:
////    Texture texture;
////    Sprite* viewPtr;
//public:
//    Unmovable(float _x, float _y, const Texture& texture) : Object() {
//        sprite.setTexture(texture);
////        sprite.setColor(Color(0, 255, 0));
////        sprite.setColor(Color(100,255,100, 100));
//        this->setX(_x);
//        this->setY(_y);
//    }
//    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
//    friend sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable);
//};
//
//class Player : public Object {
//public:
//    Player(float _x, float _y, const Texture& texture) : Object() {
//        sprite.setTexture(texture);
//        this->setX(_x);
//        this->setY(_y);
//        sprite.scale(1, 1);
////        sprite.setColor(Color(100, 1, 1, 100));
//    }
////    void draw(RenderWindow& window) {
////        window.draw(sprite);
////    }
//    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
//    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
//};
//
//sf::Packet& operator << (sf::Packet& packet, const bool* directions) {  // Запись в пакет направлений движения.
//    return packet << directions[0] << directions[1] << directions[2] << directions[3];
//}
//sf::Packet& operator >> (sf::Packet& packet, Player& player) {
//    float x, y;
//    packet >> x >> y;
//    player.setX(x);
//    player.setY(y);
////    std::cout << x << " " << y << std::endl;
//    return packet;
//}
//sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable) {
//    float x, y;
//    packet >> x >> y;
//    unmovable.setX(x);
//    unmovable.setY(y);
//    return packet;
//}



int main() {
    setlocale(LC_ALL, "");
    
    sf::TcpSocket socket;  // Создаем сокет. У каждого клиента - свой сокет.
    socket.connect("127.0.0.1", 3000);  // Подключаемся к серверу по заданному порту.
    
    sf::Packet packet;  // Создаём пакет для общения клиента с сервером.
    Texture amogusTexture;
    amogusTexture.loadFromFile("../include/textures/amogus.png");
    sf::Texture babyTexture;
    babyTexture.loadFromFile("../include/textures/baby.png");
    Texture gachiTexture;
    gachiTexture.loadFromFile("../include/textures/gachi.png");
    Texture kotTexture;
    kotTexture.loadFromFile("../include/textures/kot.jpg");
    Texture tntTexture;
    tntTexture.loadFromFile("../include/textures/tnt.png");

    std::vector<Player> players(2, Player(0, 0, amogusTexture));  // Инициализируем начальное положение объектов на карте, принимая данные от сервера.


//    Sprite gachiSprite(gachiTexture);
    std::vector<Unmovable> unmovables(1, Unmovable(200, 200, gachiTexture));
//    Ball ball(0, 0, sf::Color::Black, 15);
//    players.push_back(ball);

    sf::RenderWindow window(sf::VideoMode(500, 500), "Squid game");  // Создаём игровое окно.

//    if (typeid(objects[2]).name() == typeid(Object).name()) {std::cout << "JOPA"; return 1;}
    while (window.isOpen()) {
        // Получение информации обо всех шарах.
//        sf::CircleShape circle;
        for (auto &player : players) {  // Пробегаем по всем шарам. На 1 шар 1 пакет.
            socket.receive(packet);  // Получаем пакет.
            packet >> player;  // Записываем данные из пакета в текущую структуру шара.
            packet.clear();

            std::cout << player.getX() << ' ' << player.getY() << std::endl;  // Дебаг.
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

            std::cout << unmovable.getX() << ' ' << unmovable.getY() << std::endl;  // Дебаг.
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