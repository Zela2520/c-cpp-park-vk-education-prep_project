#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include "../include/model.h"
using namespace sf;
using namespace std;



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

    sf::Packet packet;  //// Создаём пакет для общения клиента с сервером.

    std::vector<Player> players(clients.size(), Player(0, 0, amogusTexture));  //// Задаём начальное положение массиву игроков.

    std::vector<Unmovable> unmovables(1, Unmovable(200, 200, gachiTexture));   //// Создаём одну стенку.


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
    }




    while (true) {
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
                players[i].goUp(0.3);
                if (players[i].intersectsWith(unmovables)) players[i].goDown(0.3);
            }
            if (directions[1]) {  //// Направо.
                players[i].goRight(0.3);
                if (players[i].intersectsWith(unmovables)) players[i].goLeft(0.3);
            }
            if (directions[2]) {  //// Вниз.
                players[i].goDown(0.3);
                if (players[i].intersectsWith(unmovables)) players[i].goUp(0.3);
            }
            if (directions[3]) {  //// Налево.
                players[i].goLeft(0.3);
                if (players[i].intersectsWith(unmovables)) players[i].goRight(0.3);
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
        }
    }
    return 0;
}