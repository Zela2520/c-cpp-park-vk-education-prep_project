#include "../../include/model.h"
#include "../../include/player.h"
#include "../../include/wall.h"
#include "../../include/mob.h"
#include "../../include/map.h"
#include "../../include/bullet.h"

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
    Texture pirateTexture;
    pirateTexture.loadFromFile("../include/textures/pirate.png");
    sf::Texture laserTexture;
    laserTexture.loadFromFile("../include/textures/laser.png");


    std::vector<Player> players(2, Player(700, 700, amogusTexture));  //// Инициализируем начальное положение объектов на карте, принимая данные от сервера


    sf::Texture wallTexture;
    wallTexture.loadFromFile("../include/textures/pinkBrick.jpg");
    Map map("../include/initialMap", wallTexture, wallTexture);
//    map.creat_map(walls, &gachiTexture);

//    camera.zoom(3);

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("../include/textures/sky.png");
    Sprite background(backgroundTexture);
    background.setScale(4, 4);


    RenderWindow window(sf::VideoMode(500, 500), "Client " + to_string(ID));  //// Создаём игровое окно.
    window.clear(sf::Color::White); //// заливаем его в белый цвет.
    View camera;
    camera.setSize(window.getSize().x * 3, window.getSize().y * 3);


    sf::Font lobster;
    lobster.loadFromFile("../include/fonts/lobster.ttf");
    sf::Text text;
    text.setString("Просто Чел");
    text.setFont(lobster);
    text.setColor(sf::Color::White);
    text.setCharacterSize(80);

    while (window.isOpen()) {
//        cout << "WINDOW" << window.getSize().x << " x " << window.getSize().y << endl;
        window.clear(sf::Color::Blue);
//        cout << ID;

        //// Получение информации обо всех игроках.
        for (auto &player : players) {  //// Пробегаем по всем игрокам. На 1 игрока 1 пакет.
            socket.receive(packet);  //// Получаем пакет.
            packet >> player;  //// Записываем данные из пакета в игрока.
            packet.clear();
        }


        background.setPosition(players[ID].getX() - background.getGlobalBounds().width/2, players[ID].getY() - background.getGlobalBounds().height/2);
        window.draw(background);
        map.draw(window);

        for (auto &player: players) {    //// Рисуем игроков
            player.draw(window);
        }
        //// Получение информации обо всех неподвижных объектах.
//        socket.receive(packet);
//        int amountOfWalls;
//        packet >> amountOfWalls;
//        packet.clear();
//        std::vector<Wall> walls(amountOfWalls);
////        cout << "walls.size()" << walls.size() << endl;
//        for (auto &wall : walls) {    ////  Получаем инфу о стенах
//            socket.receive(packet);
//            packet >> wall;
//            packet.clear();
////          std::cout << "Корды Гачимучи" << wall.getX() << ' ' << wall.getY() << std::endl;
//        }

        socket.receive(packet);
        int amountOfBullets;
        packet >> amountOfBullets;
        packet.clear();
        std::vector<Bullet> bullets(amountOfBullets, Bullet(0, 0, 45, laserTexture));
        for (auto &bullet : bullets) {    ////  Получаем инфу о стенах
            socket.receive(packet);
            packet >> bullet;
            packet.clear();
//          std::cout << "Корды Гачимучи" << wall.getX() << ' ' << wall.getY() << std::endl;
        }
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }

        socket.receive(packet);
        int amountOfMobs;
        packet >> amountOfMobs;
        packet.clear();
        std::vector<Mob> mobs(amountOfMobs, Mob(1000, 1000, pirateTexture));
        for (auto& mob : mobs) {    ////  Получаем инфу о стенах
            socket.receive(packet);
            packet >> mob;
            packet.clear();
//          std::cout << "Корды Гачимучи" << wall.getX() << ' ' << wall.getY() << std::endl;
        }
//        cout << mobs[0].getX() << " " << mobs[0].getY() << endl;
        for (auto& mob : mobs) {
            mob.draw(window);
        }


//        cout << players[ID].getX() << " " << players[ID].getY() << endl;



        //// чистим окно перед отрисовкой




        ///// отрисовываем все объекты на карте
        //// можно добавить ассинхронность. Тут нарисуются Unmovables
//        mob.moveMob(players[1]);
//        mob.draw(window);
        //// а тут сделать join

        text.setPosition(players[ID].getX() - 250, players[ID].getY() - 100);
        window.draw(text);

        window.display();


        sf::Event event{}; //// Переменная для отслеживания событий, происходящих на кажой итерации цикла
        bool directions[4] = {false, false, false, false};  //// Направления движения, которые будут обрабатываться на сервере.
        bool isLMBPressed = false;
        bool isWindowResized = false;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        int mouseX, mouseY;

        if (window.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                directions[0] = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                directions[1] = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                directions[2] = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                directions[3] = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                isLMBPressed = true;
            }
            if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
                isLMBPressed = true;
            }
            if (event.type == sf::Event::Resized) {
                isWindowResized = true;
                camera.setSize(event.size.width * 3, event.size.height * 3);
//                camera.zoom(3);
            }
        }

        camera.setCenter(players[ID].getX() ,players[ID].getY());
        window.setView(camera);

        packet << directions;
        socket.send(packet);
        packet.clear();

        packet << isWindowResized;
        socket.send(packet);
        packet.clear();
        if (isWindowResized) {
            packet << (double)event.size.width << (double)event.size.height;
            socket.send(packet);
            packet.clear();
        }

        packet << isLMBPressed;
        socket.send(packet);
        packet.clear();
        if (isLMBPressed) {
            packet << Mouse::getPosition(window).x << Mouse::getPosition(window).y;
            cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
            socket.send(packet);
            packet.clear();
        }
    }
    return 0;
}

