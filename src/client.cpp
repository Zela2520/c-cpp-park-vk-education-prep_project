#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "../include/model.h"
using namespace sf;
using namespace std;



int main() {
    setlocale(LC_ALL, "");
    
    sf::TcpSocket socket;  //// Создаем сокет. У каждого клиента - свой сокет.
    socket.connect("127.0.0.1", 3000);  //// Подключаемся к серверу по заданному порту.
    
    sf::Packet packet;  //// Создаём пакет для общения клиента с сервером.

    //// Все используемые в программе текстуры.
    Texture amogusTexture;
    amogusTexture.loadFromFile("/home/dima/!Stuff/TP/trying to make engine/include/textures/amogus.png");
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


    std::vector<Player> players(2, Player(0, 0, amogusTexture));  //// Инициализируем начальное положение объектов на карте, принимая данные от сервера.
    std::vector<Unmovable> unmovables(1, Unmovable(200, 200, gachiTexture));
    std::vector<Turret> turrets(1, Turret(-300, -300, babyTexture));
//    std::vector<Bullet> bullets(1, Bullet(turrets[0].getX(), turrets[0].getY(), 0, laserTexture));



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

            std::cout << "Корды игрока: " << player.getX() << ' ' << player.getY() << std::endl;  // Дебаг.
        }

        camera.setCenter(players[ID].getX() ,players[ID].getY());
        window.setView(camera);
        window.clear(sf::Color::White);
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

        for (auto& turret : turrets) {
            socket.receive(packet);
            packet >> turret;
            packet.clear();
        }
        for (auto& turret : turrets) {
            turret.draw(window);
        }

        socket.receive(packet);
        int amountOfBullets;
        packet >> amountOfBullets;
        std::vector<Bullet> bullets(0);
        for (int i = 0; i < amountOfBullets; i++) {
            socket.receive(packet);
//            bullets.emplace_back(Bullet());
//            packet >> bullets[i];
            Bullet tempBullet;
            packet >> tempBullet;
            bullets.emplace_back(Bullet(tempBullet.getX(), tempBullet.getY(), tempBullet.getRotation(), laserTexture));
            packet.clear();
        }
        for (auto& bullet : bullets) {
            bullet.draw(window);
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
//                camera.move(0,-0.3);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                directions[1] = true;
//                camera.move(0.3,0);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                directions[2] = true;
//                camera.move(0,0.3);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                directions[3] = true;
//                camera.move(-0.3,0);
            }
        }

        //// Запаковываем данные пользователя в пакет и отправляем на сервер
        packet << directions;
        socket.send(packet);
        packet.clear();
//        std::cout << directions << '\n';  // Дебаг
    }
    return 0;
}