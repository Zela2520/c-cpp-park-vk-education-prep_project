#include "../../include/danya_server.h"
#include <iostream>
#include "../../include/map.h"

#define MAX_NUMBER_OF_CLIENTS 2
#define INIT_ID 0


Server::Server(int _port) {
    port = _port;
    clients = new std::vector<sf::TcpSocket>(2);
    sf::Texture wallTexture;
    wallTexture.loadFromFile("../include/textures/brick.png");
    setConnection();
    receiveClients();
    map = new Map((char*)"../include/initialMap", wallTexture, wallTexture);
    load_pictures(pictures);
    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; i++) {
        players.emplace_back(100, 100, pictures.amogusTexture);
        players[i].setId(i);
    }
    std::cout << "Server was started\n";
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

    for (auto& client : *clients) {
        if (listener.accept(client) != sf::Socket::Done) {
            std::cerr << "The server is not ready to accept the client";
            exit(1);
        }

        id = INIT_ID;
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

    for (auto& client : *clients) {
        for (auto& cur_player : players) {
            packet << cur_player;
            client.send(packet);
            packet.clear();
            std::cout << "ДАННЫЕ БЫЛИ ОТПРАВЛЕНЫ\n";
        }
        packet << (int)(map->getWalls().size());
        client.send(packet);
        packet.clear();
        for (auto& wall : map->getWalls()) {   //// И о каждом несдвигаемом объекте.
            packet << wall;
            client.send(packet);
            packet.clear();
        }
    }
}

void Server::processAcquiredData() {
    std::cout << "НАЧИНАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time /= 400;

    for (auto& client : *clients) {
        client.receive(packet);
        bool directions[4];
        packet >> directions;  //// Достаём информацию из пакета.
        packet.clear();

        //// Обрабатываем полученную информацию о направлении.
        if (directions[0]) {   //// Вверх.
            players[0].goUp(0.3 * time);
            if (players[0].intersectsWith(map->getWalls())) players[0].goDown(0.3 * time);
        }
        if (directions[1]) {  //// Направо.
            players[0].goRight(0.3 * time);
            if (players[0].intersectsWith(map->getWalls())) players[0].goLeft(0.3 * time);
        }
        if (directions[2]) {  //// Вниз.
            players[0].goDown(0.3 * time);
            if (players[0].intersectsWith(map->getWalls())) players[0].goUp(0.3 * time);
        }
        if (directions[3]) {  //// Налево.
            players[0].goLeft(0.3 * time);
            if (players[0].intersectsWith(map->getWalls())) players[0].goRight(0.3 * time);
        }
    }

    std::cout << "ЗАКАНЧИВАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
}

void Server::start_server() {
    std::cout << "СТАРТ";
    while (true) {
        processAcquiredData();
        std::cout << "ДАННЫЕ ДОЛЖНЫ УЛЕТЕТЬ КЛИЕНТУ";
        sendData();
        std::cout << "ДАННЫЕ УЛЕТЕЛИ КЛИЕНТУ";
    }
}

void Server::load_pictures(Pictures &pictures) {
    Pictures init_pictures("../include/textures/amogus.png", "../include/textures/tnt.png");
    pictures = init_pictures;
}