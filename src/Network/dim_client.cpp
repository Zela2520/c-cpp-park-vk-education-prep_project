
#include "../../include/model.h"
#include "../../include/player.h"
#include "../../include/wall.h"
#include "../../include/mob.h"
#include "../../include/map.h"

#include <string>
#include <iostream>

using namespace sf;
using namespace std;

int main() {
    setlocale(LC_ALL, "");

    sf::TcpSocket socket;  //// Создаем сокет. У каждого клиента - свой сокет.
    socket.connect("127.0.0.1", 3000);  //// Подключаемся к серверу по заданному порту.

    sf::Packet packet;  //// Создаём пакет для общения клиента с сервером.
    int ID = -1;
    socket.receive(packet);
    packet >> ID;
    packet.clear();

    //// Все используемые в программе текстуры.
    Texture amogusTexture;
    amogusTexture.loadFromFile("../include/textures/amogus.png");
    Texture gachiTexture;
    gachiTexture.loadFromFile("../include/textures/tnt.png");
    Texture mobTexture;
    mobTexture.loadFromFile("../include/textures/tnt.png");

    Mob mob(200.0,200.0, mobTexture);
    mob.setScale(0.8,0.8);
    std::vector<Player> players(2, Player(100, 100, amogusTexture));  //// Инициализируем начальное положение объектов на карте, принимая данные от сервера


    sf::Texture wallTexture;
    wallTexture.loadFromFile("../include/textures/brick.png");
    Map map("../include/initialMap", wallTexture, wallTexture);
//    map.creat_map(walls, &gachiTexture);
    View camera;
    camera.zoom(2);


    RenderWindow window(sf::VideoMode(500, 500), "Client " + to_string(ID));  //// Создаём игровое окно.
    window.clear(sf::Color::White); //// заливаем его в белый цвет

    while (window.isOpen()) {
        window.clear(sf::Color::Blue);
//        cout << ID;

        map.draw(window);
        //// Получение информации обо всех игроках.
        for (auto &player : players) {  //// Пробегаем по всем игрокам. На 1 игрока 1 пакет.
            socket.receive(packet);  //// Получаем пакет.
            packet >> player;  //// Записываем данные из пакета в игрока.
            packet.clear();
        }
        for (auto &player: players) {    //// Рисуем игроков
            if (ID == 1) player.getSprite().setColor(sf::Color(0, 255, 0));
            player.draw(window);
        }
        //// Получение информации обо всех неподвижных объектах.
        socket.receive(packet);
        int amountOfWalls;
        packet >> amountOfWalls;
        packet.clear();
        std::vector<Wall> walls(amountOfWalls);
        cout << "walls.size()" << walls.size() << endl;
        for (auto &wall : walls) {    ////  Получаем инфу о стенах
            socket.receive(packet);
            packet >> wall;
            packet.clear();
//          std::cout << "Корды Гачимучи" << wall.getX() << ' ' << wall.getY() << std::endl;
        }
//        cout << players[ID].getX() << " " << players[ID].getY() << endl;
        camera.setCenter(players[ID].getX() ,players[ID].getY());
        window.setView(camera);


        //// чистим окно перед отрисовкой




        ///// отрисовываем все объекты на карте
        //// можно добавить ассинхронность. Тут нарисуются Unmovables
        mob.moveMob(mob.setTaregt(players), map.getWalls());
        mob.draw(window);
        //// а тут сделать join



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

