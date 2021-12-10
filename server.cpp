#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "model.h"
using namespace sf;
using namespace std;

//struct Ball {
//    int x;
//    int y;
//    std::string color;
//};

//class Object {
//protected:
//    CircleShape border;
//    Sprite sprite;
//public:
////    explicit Object(const Texture& texture) {
////        sprite = new Sprite(texture);
////    }
//    Sprite& getSprite() {
//        return sprite;
//    }
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
//        sprite.setPosition(this->getX(), this->getY() - distance);
//    }
//    void goDown(float distance = 1) {
//        sprite.setPosition(this->getX(), this->getY() + distance);
//    }
//    void goRight(float distance = 1) {
//        sprite.setPosition(this->getX() + distance, this->getY());
//    }
//    void goLeft(float distance = 1) {
//        sprite.setPosition(this->getX() - distance, this->getY());
//    }
//    void draw(RenderWindow& window) {
//        window.draw(sprite);
//        window.draw(border);
//    }
////    virtual bool intersectsWith(vector<Object>& objects);
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
//////       return color;
//////    }
//////    Color setColor(sf::Color _color) const {
//////        color = _color;
//////    }
////
////};
//
//class Unmovable : public Object {
//private:
////    Texture texture;
////    Sprite* viewPtr;
//public:
//    Unmovable(float _x, float _y, const String& filename) : Object() {
//        Texture texture;
//        texture.loadFromFile(filename);
//        sprite.setTexture(texture);
//        this->setX(_x);
//        this->setY(_y);
//    }
//    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
//};
//
//class Player : public Object {
//public:
//    Player(float _x, float _y, const String& filename) : Object() {
//        Texture texture;
//        texture.loadFromFile(filename);
//        sprite.setTexture(texture);
////        sprite.scale(0.1, 0.1);  // Масштабировани модели
//        this->setX(_x);
//        this->setY(_y);
//    }
//    bool intersectsWith(vector<Unmovable>& objects) {
//        for (auto& object : objects) {
//            Rect<float> thisBounds = sprite.getGlobalBounds();
//            Rect<float> objectBounds = object.getSprite().getGlobalBounds();
//
//            border.setPointCount(4);
//            border.setPosition(thisBounds.left, thisBounds.top);
//            border.setRadius(thisBounds.width);
//            border.setOutlineColor(Color::Green);
//            border.setOutlineThickness(10);
//
//            Rect<float> scaledThisBounds(thisBounds.left, thisBounds.top, thisBounds.width*1, thisBounds.height*1);
//            Rect<float> scaledObjectBounds(objectBounds.left, objectBounds.top, objectBounds.width*1, objectBounds.height*1);
//            if (scaledThisBounds.intersects((scaledObjectBounds))) {
//                std::cout << "ПЕРЕСЕЧЕНИЕ" << endl;
//                cout << scaledThisBounds.left << " " << scaledThisBounds.top << " " << scaledThisBounds.height << " " << scaledThisBounds.width << endl;
//                cout << scaledObjectBounds.left << " " << scaledObjectBounds.top << " " << scaledObjectBounds.height << " " << scaledObjectBounds.width << endl;
//                return true;
//            }
//        }
//        return false;
//    }
//    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
//    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
//};
//
//
//sf::Packet& operator << (sf::Packet& packet, const Player& player) {
//    return packet << player.getX() << player.getY();
//}
////
//sf::Packet& operator >> (sf::Packet& packet, Player& player) {
//    float x, y;
//    packet >> x >> y;
//    player.setX(x);
//    player.setY(y);
//    return packet;
//}
//
//sf::Packet& operator >> (sf::Packet& packet, bool* directions) {
//    return packet >> directions[0] >> directions[1] >> directions[2] >> directions[3];
//}
//sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable) {
//    return packet << unmovable.getX() << unmovable.getY();
//}
////
////class Map {
////private:
////    vector<Player>* players;
////    vector<Unmovable>* unmovables;
////public:
////    Map(vector<Player>* _players, vector<Unmovable>* _unmovables) {
////        players = _players;
////        unmovables = _unmovables;
////    }
////};


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


//    sf::Texture gachiTexture;
//    gachiTexture.loadFromFile("/home/dima/!Stuff/TP/trying to make engine/baby.png");
//    Sprite gachiSprite(gachiTexture);
    std::vector<Unmovable> unmovables(1, Unmovable(200, 200));

    sf::Packet packet;  // Для передачи даннных между клиент сервером создаём пакет, который будет летать по сети.
    std::vector<Player> players(clients.size(), Player(0, 0));  // инициализируем клиентов значниями по умолчанию.
    // Заранее отправляем клиентам данные о том, что мячи расположены на нулевых координатах.
    for (auto & client : clients) {  // Для каждого клиента.
        for (auto & player : players) {   // О каждом игроке.
            packet << player;
            client.send(packet);
            packet.clear();
            
//            std::cout << player.getX() << ' ' << player.getY() << std::endl;  // Дебаг.
        }
        for (auto & unmovable : unmovables) {   // О каждом несдвигаемом объекте
            packet << unmovable;
            client.send(packet);
            packet.clear();

//            std::cout << unmovable.getX() << ' ' << unmovable.getY() << '\n';  // Дебаг.
        }
    }




    while (true) {
        // получаем пакет с информацией о перемещении какждого клиента и извлекаем информацию о перемещение каждого клиента
        // перемещение i-ого клиента значит перемещение i-ого мячика
        for (int i = 0; i < clients.size(); ++i) {
            // указывем направление движения объекта
            clients[i].receive(packet);
            bool directions[4];
            packet >> directions;
            packet.clear();
//            std::cout << directions << "\n";  // Дебаг.

            // обрабатываем действие пользователя
            if (directions[0]) {
                players[i].goUp(0.3);
                if (players[i].intersectsWith(unmovables)) players[i].goDown(0.3);
            }
            if (directions[1]) {
                players[i].goRight(0.3);
                if (players[i].intersectsWith(unmovables)) players[i].goLeft(0.3);
            }
            if (directions[2]) {
                players[i].goDown(0.3);
                if (players[i].intersectsWith(unmovables)) players[i].goUp(0.3);
            }
            if (directions[3]) {
                players[i].goLeft(0.3);
                if (players[i].intersectsWith(unmovables)) players[i].goRight(0.3);
            }
        }

        // отправляем обновлённые данные об изменение всех объектов на сервере каждому клиенту
        for (auto & client : clients) {
            for (auto & player : players) {
                packet << player;
                client.send(packet);
                packet.clear();
//                std::cout << player.getX() << ' ' << player.getY() << '\n';
            }
            for (auto & unmovable : unmovables) {   // О каждом несдвигаемом объекте
                packet << unmovable;
                client.send(packet);
                packet.clear();

//            std::cout << unmovable.getX() << ' ' << unmovable.getY() << '\n';  // Дебаг.
            }
        }
    }
    return 0;
}