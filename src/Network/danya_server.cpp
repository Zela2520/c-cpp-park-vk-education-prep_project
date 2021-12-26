#include "../../include/danya_server.h"
#include <iostream>
#include "../../include/map.h"
#include "../../include/model.h"

#define MAX_NUMBER_OF_CLIENTS 2
#define INIT_ID 0


Server::Server(int _port) {
    port = _port;
    clients = new std::vector<sf::TcpSocket>(2);
    spawnpoint = sf::Vector2<float>(400,400);
    amogusTexture.loadFromFile("../include/textures/amogus.png");
    gachiTexture.loadFromFile("../include/textures/gachi.png");
    globalWallTexture.loadFromFile("../include/textures/pinkBrick.jpg");
    localWallTexture.loadFromFile("../include/textures/pinkBrick.jpg");
    pirateTexture.loadFromFile("../include/textures/pirate.png");
    laserTexture.loadFromFile("../include/textures/laser.png");
    pirateTexture.loadFromFile("../include/textures/pirate.png");
    setConnection();
    receiveClients();
    map = new Map((char*)"../include/initialMap", globalWallTexture, localWallTexture);
//    load_pictures(pictures);
    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; i++) {
        players.emplace_back(500, 500, amogusTexture);
        players[i].setId(i);
    }
    for (int i = 0; i < 4; i++) {
        mobs.emplace_back(3000 - rand()%2000, 3000 - rand()%2000, pirateTexture);
        if (badSpawn(mobs[mobs.size() - 1])) {
            mobs.pop_back();
            std::cout << "УДАЛЁН" << std::endl;
        }
    }
    std::cout << "Server was started\n";
}

bool Server::badSpawn(Mob& mob) {
    bool intersects = false;
    for (auto& player : players) {
        if (mob.getSprite().getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
            intersects = true;
        }
    }
    for (auto& wall : map->getWalls()) {
        if (mob.getSprite().getGlobalBounds().intersects(wall.getSprite().getGlobalBounds())) {
            intersects = true;
        }
    }
    for (int i = 0; i < mobs.size() - 1; i++) {
        if (mob.getSprite().getGlobalBounds().intersects(mobs[i].getSprite().getGlobalBounds())) {
            intersects = true;
        }
    }
    return intersects;
}

void Server::setConnection() {
    std::cout << "Сервер должен начать слушать\n";
    if (listener.listen(port) != sf::Socket::Done) {
        std::cerr << "The server is not ready to accept the client";
        exit(1);
    }

    std::cout << "Сервер начал слушать\n";
}

void Server::receiveClients() {
    std::cout << "Сервер должен принять клиента\n";

    id = 0;
    for (auto& client : *clients) {
        if (listener.accept(client) != sf::Socket::Done) {
            std::cerr << "The server is not ready to accept the client";
            exit(1);
        }

        packet << id++;
        client.send(packet);
        packet.clear();
    }
    std::cout << "Сервер принял клиентов\n";
}

void Server::sendData() {
    std::cout << "ДАННЫЕ ДОЛЖНЫ БЫТЬ ОТПРАВЛЕНЫ\n";

    //// кусок ниже можно сделать ассинхроно, добавив функцию void и передавая в неё нужного клиента.

    //// Отправляем данные первому клиенту
    for (int i = 0; i < clients->size(); i++) {
        for (auto& player : players) {
            packet << player;
            (*clients)[i].send(packet);
            packet.clear();
//            std::cout << "ДАННЫЕ БЫЛИ ОТПРАВЛЕНЫ\n";
        }

        packet << (int)(bullets.size());
        (*clients)[i].send(packet);
        packet.clear();
        for (auto& bullet : bullets) {   //// И о каждой пуле.
            packet << bullet;
            (*clients)[i].send(packet);
            packet.clear();
        }

        packet << (int)(mobs.size());
        (*clients)[i].send(packet);
        packet.clear();
        for (auto& mob : mobs) {
            packet << mob;
            (*clients)[i].send(packet);
            packet.clear();
        }

        packet << amountOfKilled;
        (*clients)[i].send(packet);
        packet.clear();

        packet << (int)spawnrateTimer.getElapsedTime().asSeconds();
        (*clients)[i].send(packet);
        packet.clear();

        packet << (int)record;
        (*clients)[i].send(packet);
        packet.clear();

        packet << (bool)players[i].getInvincibility();
        (*clients)[i].send(packet);
        packet.clear();
    }
}

void Server::processAcquiredData() {
//    std::cout << "НАЧИНАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
    float moveTime = moveTimer.getElapsedTime().asMicroseconds();
    moveTime /= 400;
    moveTimer.restart();
//
//    float reloadTime = reloadTimer.getElapsedTime().asMilliseconds();
//    reloadTime /= 500;
    for (int i = 0; i < clients->size(); i++) {
        (*clients)[i].receive(packet);
        bool directions[4];
        packet >> directions;  //// Достаём информацию из пакета.
        packet.clear();

        //// Обрабатываем полученную информацию о направлении.
        if (directions[0]) {   //// Вверх.
            players[i].goUp(0.3 * moveTime);
            if (players[i].intersectsWith(map->getWalls())) players[i].goDown(0.3 * moveTime);
        }
        if (directions[1]) {  //// Направо.
            players[i].goRight(0.3 * moveTime);
            if (players[i].intersectsWith(map->getWalls())) players[i].goLeft(0.3 * moveTime);
        }
        if (directions[2]) {  //// Вниз.
            players[i].goDown(0.3 * moveTime);
            if (players[i].intersectsWith(map->getWalls())) players[i].goUp(0.3 * moveTime);
        }
        if (directions[3]) {  //// Налево.
            players[i].goLeft(0.3 * moveTime);
            if (players[i].intersectsWith(map->getWalls())) players[i].goRight(0.3 * moveTime);
        }

        bool isWindowResized;
        (*clients)[i].receive(packet);
        packet >> isWindowResized;  //// Достаём информацию из пакета.
        packet.clear();
        if (isWindowResized) {
            (*clients)[i].receive(packet);
            packet >> windowWidth >> windowHeight;

            packet.clear();
        }
//        std::cout << windowWidth << " " << windowHeight << std::endl;


        bool isLMBPressed;
        (*clients)[i].receive(packet);
        packet >> isLMBPressed;  //// Достаём информацию из пакета.
        packet.clear();

        if (isLMBPressed) {
            int x, y;
            (*clients)[i].receive(packet);
            packet >> x >> y;
//            std::cout << "Принял " << x << " " << y << std::endl;
//            std::cout << "Имел " << players[i].getX() << " " << players[i].getY() << std::endl;
            packet.clear();
            std::cout << "Попытка создать пулю " << std::endl;
            bullets.emplace_back(players[i].getX() + players[i].getSprite().getGlobalBounds().width/3, players[i].getY() + players[i].getSprite().getGlobalBounds().height/2, getAngle(x, y, windowWidth, windowHeight), laserTexture);
            std::cout << "Пуля успешно создана " << std::endl;
        }




    }

    int amountOfDeletedBullets = 0;
    for (int i = 0; i < bullets.size(); i++) {    //// Проходим по всем пулям.
        std::cout << "Началась обработка пуль" << std::endl;
        //// Двигаем текущую пулю.
        bullets[i - amountOfDeletedBullets].move(0.8 * moveTime * cos(3.1415 / 180 * bullets[i].getRotation()), 0.8 * moveTime * sin(3.1415 / 180 * bullets[i - amountOfDeletedBullets].getRotation()));

        for (auto& wall : map->getWalls()) {    //// Проходим по всем стенкам.
            if (bullets[i - amountOfDeletedBullets].getSprite().getGlobalBounds().intersects(wall.getSprite().getGlobalBounds())) {    //// Если случилось пересечение со стеной
                bullets.erase(bullets.begin() + i - amountOfDeletedBullets);
                amountOfDeletedBullets++;
                break;
            }
        }
    }

    int amountOfDeletedMobs = 0;
    amountOfDeletedBullets = 0;
    for (int i = 0; i < mobs.size(); i++) {
        std::cout << "Началась обработка мобов" << std::endl;
        mobs[i - amountOfDeletedMobs].moveMob(mobs[i - amountOfDeletedMobs].setTaregt(players), map->getWalls(), moveTime);
        bool intersects = false;

        for (int j = 0; j < bullets.size(); j++) {
            if (bullets[j].getSprite().getGlobalBounds().intersects(mobs[i - amountOfDeletedMobs].getSprite().getGlobalBounds())) {    //// Если случилось пересечение со стеной
                intersects = true;
                mobs.erase(mobs.begin() + i - amountOfDeletedMobs);
                amountOfDeletedMobs++;
                this->amountOfKilled++;
                bullets.erase(bullets.begin() + j - amountOfDeletedBullets);
                amountOfDeletedBullets++;
                break;
            }
        }

        if (!intersects) {
            for (int j = 0; j < mobs.size(); j++) {
                if (j != i - amountOfDeletedMobs) {
                    if (mobs[j].getSprite().getGlobalBounds().intersects(mobs[i - amountOfDeletedMobs].getSprite().getGlobalBounds())) {    //// Если случилось пересечение со стеной
                        intersects = true;
                        mobs.erase(mobs.begin() + i - amountOfDeletedMobs);
                        amountOfDeletedMobs++;
//                    this->amountOfKilled++;
//                    bullets.erase(bullets.begin() + j - amountOfDeletedBullets);
//                    amountOfDeletedBullets++;
                        break;
                    }
                }
            }
        }


        if (!intersects) {
            std::cout << "Пересечение мобов с игроками" << std::endl;
            for (auto & player : players) {
                if (player.getSprite().getGlobalBounds().intersects(mobs[i - amountOfDeletedMobs].getSprite().getGlobalBounds())) {
                    if (player.getInvincibility() == false) {
                        player.setX(spawnpoint.x);
                        player.setY(spawnpoint.y);
                        player.setInvincibility(true);
                        player.resetInvincibilityTimer();

                        if (amountOfKilled > record) {
                            record = amountOfKilled;
                        }
                        amountOfKilled = 0;
                    }
                }
            }
            std::cout << "Пережил пересечение мобов с игроками" << std::endl;
        }
    }

    for (auto& player: players) {
        if (player.getElapsedInvincibilityTime() > 4000) {
            player.setInvincibility(false);
            player.resetInvincibilityTimer();
        }
    }


    float newSpawnTime = newSpawnTimer.getElapsedTime().asSeconds();
//    std::cout << elapsedTime;
    float spawnRateTime = spawnrateTimer.getElapsedTime().asSeconds();
    if (newSpawnTime > 1) {
        for (int i = 0; i < 30; i++) {
            mobs.emplace_back(  1000 + rand() % 3000, 1000 + rand() % 3000, pirateTexture);
            if (badSpawn(mobs[mobs.size() - 1])) {
                mobs.pop_back();
            }
        }
        newSpawnTimer.restart();
    }


    std::cout << "ЗАКАНЧИВАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
}

void Server::startServer() {
    std::cout << "СТАРТ";
    while (true) {
        processAcquiredData();
//        std::cout << "ДАННЫЕ ДОЛЖНЫ УЛЕТЕТЬ КЛИЕНТУ";
        sendData();
//        std::cout << "ДАННЫЕ УЛЕТЕЛИ КЛИЕНТУ";
    }
}

//void Server::load_pictures(Pictures &pictures) {
//    Pictures init_pictures("../include/textures/amogus.png", "../include/textures/tnt.png");
//    pictures = init_pictures;
//}