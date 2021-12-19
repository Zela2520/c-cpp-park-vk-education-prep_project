#include "../../include/model.h"
#include "../../include/player.h"
#include "../../include/unmovable.h"
#include "../../include/mob.h"

#include <iostream>

using namespace sf;
using namespace std;



int main() {
    setlocale(LC_ALL, "");

    sf::TcpSocket socket;  //// Создаем сокет. У каждого клиента - свой сокет.
    socket.connect("127.0.0.1", 3000);  //// Подключаемся к серверу по заданному порту.

    sf::Packet packet;  //// Создаём пакет для общения клиента с сервером.

    //// Все используемые в программе текстуры.
    Texture amogusTexture;
    amogusTexture.loadFromFile("../include/textures/amogus.png");
    Texture gachiTexture;
    gachiTexture.loadFromFile("../include/textures/gachi.png");


    Texture mobTexture;
    mobTexture.loadFromFile("../include/textures/amogus.png");
    Mob mob(-500.0,-500.0,mobTexture);
    mob.setScale(0.5,0.5);
    std::vector<Player> players(2, Player(0, 0, amogusTexture));  //// Инициализируем начальное положение объектов на карте, принимая данные от сервера.
    std::vector<Unmovable> unmovables(1, Unmovable(200, 200, gachiTexture));


    RenderWindow window(sf::VideoMode(500, 500), "Squid game");  //// Создаём игровое окно.
    View camera;
    camera.zoom(1);
    camera.setCenter(players[0].getX(), players[0].getY());
    int ID = -1;
    socket.receive(packet);
    packet >> ID;


    while (window.isOpen()) {
        //// Получение информации обо всех игроках.
        for (auto &player : players) {  //// Пробегаем по всем игрокам. На 1 игрока 1 пакет.
            socket.receive(packet);  //// Получаем пакет.
            packet >> player;  //// Записываем данные из пакета в игрока.
            packet.clear();

            //std::cout << "Корды игрока: " << player.getX() << ' ' << player.getY() << std::endl;  // Дебаг.
        }
        mob.moveMob(players[1]);
        mob.draw(window);
        camera.setCenter(players[ID].getX() ,players[ID].getY());
        window.setView(camera);
        window.clear(sf::Color::White);
        mob.draw(window);
        //// Отрисовка всех игроков.
        for (auto &player : players) {
            player.draw(window);
        }
        for (auto &unmovable : unmovables) {
            socket.receive(packet);
            packet >> unmovable;
            packet.clear();

            std::cout << "Корды Гачимучи" << unmovable.getX() << ' ' << unmovable.getY() << std::endl;
        }
        for (auto& unmovable : unmovables) {
            unmovable.draw(window);
        }
        window.display();


        sf::Event event{}; //// Переменная для отслеживания событий, происходящих на кажой итерации цикла
        bool directions[4] = {false, false, false, false};  //// Направления движения, которые будут обрабатываться на сервере.
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

        //// Запаковываем данные пользователя в пакет и отправляем на сервер
        packet << directions;
        socket.send(packet);
        packet.clear();
    }
    return 0;
}

