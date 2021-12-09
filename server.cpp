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
    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
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
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
};

sf::Packet& operator << (sf::Packet& packet, const Player& player) {
    return packet << player.x << player.y;
}
//
sf::Packet& operator >> (sf::Packet& packet, Player& player) {
    return packet >> player.x >> player.y;
}

sf::Packet& operator >> (sf::Packet& packet, bool* directions) {
    return packet >> directions[0] >> directions[1] >> directions[2] >> directions[3];
}
sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable) {
    return packet << unmovable.x << unmovable.y;
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


    sf::Texture gachiTexture;
    gachiTexture.loadFromFile("/home/dima/!Stuff/TP/trying to make engine/baby.png");
    Sprite gachiSprite(gachiTexture);
    std::vector<Unmovable> unmovables(1, Unmovable(200, 200, gachiSprite));

    sf::Packet packet;  // Для передачи даннных между клиент сервером создаём пакет, который будет летать по сети.
    std::vector<Player> players(clients.size(), Player(0, 0, sf::Color::Black, 15));  // инициализируем клиентов значниями по умолчанию.
    // Заранее отправляем клиентам данные о том, что мячи расположены на нулевых координатах.
    for (auto & client : clients) {  // Для каждого клиента.
        for (auto & player : players) {   // О каждом игроке.
            packet << player;
            client.send(packet);
            packet.clear();
            
            std::cout << player.getX() << ' ' << player.getY() << '\n';  // Дебаг.
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
                players[i].goUp();
            }
            if (directions[1]) {
                players[i].goRight();
            }
            if (directions[2]) {
                players[i].goDown();
            }
            if (directions[3]) {
                players[i].goLeft();
            }
        }

        // отправляем обновлённые данные об изменение всех объектов на сервере каждому клиенту
        for (auto & client : clients) {
            for (auto & player : players) {
                packet << player;
                client.send(packet);
                packet.clear();
                std::cout << player.getX() << ' ' << player.getY() << '\n';
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