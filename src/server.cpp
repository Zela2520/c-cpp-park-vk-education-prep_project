#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "../include/model.h"
using namespace sf;
using namespace std;



int main(int argc, char* argv[]) {
    sf::TcpListener listener;
    //// Устанавливаем по какому порту будет проходить подключение к серверу
    if (listener.listen(3000) != sf::Socket::Done) {  //// Слушаем порт 3000.
        std::cerr << "Error";
    }
    sf::Packet packet;  //// Создаём пакет для общения клиента с сервером.

    // Рассмотрим случай для двух клиентов
    std::vector<sf::TcpSocket> clients(2);
    // если кто-то подключается, то accept индентифицирует клиента для дальнешей работы с ним
    for (int i = 0; i < clients.size(); i++) {
        listener.accept(clients[i]);
        packet << i;
        clients[i].send(packet);
        packet.clear();
    }


    //// Все используемые в программе текстуры.
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
    Texture laserTexture;
    laserTexture.loadFromFile("../include/textures/laser.png");

    std::vector<Player> players;
    for (int i = 0; i < 2; i++) {
        players.emplace_back(0, 0, amogusTexture);
        players[i].setId(i);
    }
    std::vector<Unmovable> unmovables(1, Unmovable(200, 200, gachiTexture));   //// Создаём одну стенку.
    std::vector<Turret> turrets(1, Turret(-300, -300, babyTexture));
    std::vector<Bullet> bullets(1, Bullet(turrets[0].getX(), turrets[0].getY(), 0, laserTexture));


    //// Заранее отправляем клиентам данные о том, что мячи расположены на нулевых координатах.
    for (auto & client : clients) {  //// Для каждого клиента.
        for (auto & player : players) {   //// О каждом игроке.
            packet << player;
            client.send(packet);
            packet.clear();
//            std::cout << player.getX() << ' ' << player.getY() << std::endl;  // Дебаг.
        }
        for (auto & unmovable : unmovables) {   //// И о каждом несдвигаемом объекте.
            packet << unmovable;
            client.send(packet);
            packet.clear();
//            std::cout << unmovable.getX() << ' ' << unmovable.getY() << '\n';  // Дебаг.
        }
        for (auto & turret : turrets) {
            packet << turret;
            client.send(packet);
            packet.clear();
        }
        for (auto & bullet : bullets) {
            packet << bullet;
            client.send(packet);
            packet.clear();
        }
    }


    sf::Clock clock;

    while (true) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 800;
        //// Получаем пакет с информацией о перемещении какждого клиента и извлекаем информацию о его перемещении.
        //// Перемещение i-ого клиента значит перемещение i-ого мячика.
        for (int i = 0; i < clients.size(); ++i) {
            clients[i].receive(packet);
            bool directions[4];
            packet >> directions;  //// Достаём информацию из пакета.
            packet.clear();
//            std::cout << directions << "\n";  // Дебаг.

            //// Обрабатываем полученную информацию о направлении.
            if (directions[0]) {   //// Вверх.
                players[i].goUp(0.3 * time);
                if (players[i].intersectsWith(unmovables)) players[i].goDown(0.3 * time);
            }
            if (directions[1]) {  //// Направо.
                players[i].goRight(0.3 * time);
                if (players[i].intersectsWith(unmovables)) players[i].goLeft(0.3 * time);
            }
            if (directions[2]) {  //// Вниз.
                players[i].goDown(0.3 * time);
                if (players[i].intersectsWith(unmovables)) players[i].goUp(0.3 * time);
            }
            if (directions[3]) {  //// Налево.
                players[i].goLeft(0.3 * time);
                if (players[i].intersectsWith(unmovables)) players[i].goRight(0.3 * time);
            }
        }

        //// Отправляем обновлённые данные об изменение всех объектов на сервере каждому клиенту.
        for (auto & client : clients) {  //// Каждому клиенту.
            for (auto & player : players) {    //// О каждом игроке.
                packet << player;  //// Записываем в пакет всю информацию об игроке.
                client.send(packet);
                packet.clear();
//                std::cout << player.getX() << ' ' << player.getY() << '\n';
            }
            for (auto & unmovable : unmovables) {   //// И о каждом несдвигаемом объекте.
                packet << unmovable;
                client.send(packet);
                packet.clear();

//            std::cout << unmovable.getX() << ' ' << unmovable.getY() << '\n';  // Дебаг.
            }
            for (auto & turret : turrets) {
                packet << turret;
                client.send(packet);
                packet.clear();
            }
            for (auto & bullet : bullets) {
                packet << bullet;
                client.send(packet);
                packet.clear();
            }
        }
    }
    return 0;
}