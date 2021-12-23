#include "../../include/danya_server.h"
#include <iostream>

#define MAX_NUMBER_OF_CLIENTS 2
#define INIT_ID 0


Server::Server(size_t port) {
    sf::Texture wallTexture;
    wallTexture.loadFromFile("../include/textures/brick.png");
    map = new Map("../include/initialMap", wallTexture, wallTexture);
    m_port = port;
    load_pictures(pictures);
//    m_map.creat_map(m_walls, &pictures.gachiTexture); //// можно передавать несколько текстур, чтобы объекты были разные либо передавать Pictures&, а в map подключить server_danya.h
    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; i++) {
        players.emplace_back(100, 100, pictures.amogusTexture);
        players[i].setId(i);
    }
    std::cout << "Server was started\n";
}

void Server::set_connection() {
    std::cout << "Сервер должен начать слушать\n";
    if (m_listener.listen(m_port) != sf::Socket::Done) {
        std::cerr << "The server is not ready to accept the client";
        exit(1);
    }

    std::cout << "Сервер начал слушать\n";
}

void Server::receive_clients() {
    std::cout << "Сервер должен принять клиента\n";

    if (m_listener.accept(m_client_one) != sf::Socket::Done) {
        std::cerr << "The server is not ready to accept the client";
        exit(1);
    }

    id = INIT_ID;
    packet << id;
    m_client_one.send(packet);
    packet.clear();

    if (m_listener.accept(m_client_two) != sf::Socket::Done) {
        std::cerr << "The server is not ready to accept the client";
        exit(1);
    }

    packet << ++id;
    m_client_two.send(packet);
    packet.clear();
    std::cout << "Сервер принял клиентов\n";
}

void Server::send_data() {
    std::cout << "ДАННЫЕ ДОЛЖНЫ БЫТЬ ОТПРАВЛЕНЫ\n";

    //// кусок ниже можно сделать ассинхроно, добавив функцию void и передавая в неё нужного клиента.

    //// Отправляем данные первому клиенту
    for (auto& cur_player : players) {
        packet << cur_player;
        m_client_one.send(packet);
        packet.clear();
        std::cout << "ДАННЫЕ БЫЛИ ОТПРАВЛЕНЫ\n";
    }
    packet << (int)(map->getWalls().size());
    m_client_one.send(packet);
    packet.clear();
    for (auto& wall : map->getWalls()) {   //// И о каждом несдвигаемом объекте.
        packet << wall;
        m_client_one.send(packet);
        packet.clear();
    }

    //// Отправляем данные второму клиенту
    for (auto& cur_player : players) {
        packet << cur_player;
        m_client_two.send(packet);
        packet.clear();
        std::cout << "ДАННЫЕ БЫЛИ ОТПРАВЛЕНЫ\n";
    }
    packet << (int)(map->getWalls().size());
    m_client_two.send(packet);
    packet.clear();
    for (auto& wall : map->getWalls()) {   //// И о каждом несдвигаемом объекте.
        packet << wall;
        m_client_two.send(packet);
        packet.clear();
    }
}

void Server::clients_movements() {
    std::cout << "НАЧИНАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
    float time = m_clock.getElapsedTime().asMicroseconds();
    m_clock.restart();
    time /= 400;
    m_client_one.receive(packet);
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

    m_client_two.receive(packet);
    packet >> directions;  //// Достаём информацию из пакета.
    packet.clear();

    //// Обрабатываем полученную информацию о направлении.
    if (directions[0]) {   //// Вверх.
        players[1].goUp(0.3 * time);
        if (players[1].intersectsWith(map->getWalls())) players[1].goDown(0.3 * time);
    }
    if (directions[1]) {  //// Направо.
        players[1].goRight(0.3 * time);
        if (players[1].intersectsWith(map->getWalls())) players[1].goLeft(0.3 * time);
    }
    if (directions[2]) {  //// Вниз.
        players[1].goDown(0.3 * time);
        if (players[1].intersectsWith(map->getWalls())) players[1].goUp(0.3 * time);
    }
    if (directions[3]) {  //// Налево.
        players[1].goLeft(0.3 * time);
        if (players[1].intersectsWith(map->getWalls())) players[1].goRight(0.3 * time);
    }

    std::cout << "ЗАКАНЧИВАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
}

void Server::start_server() {
    std::cout << "СТАРТ";
    while (true) {
        clients_movements();
        std::cout << "ДАННЫЕ ДОЛЖНЫ УЛЕТЕТЬ КЛИЕНТУ";
        send_data();
        std::cout << "ДАННЫЕ УЛЕТЕЛИ КЛИЕНТУ";
    }
}

void Server::load_pictures(Pictures &pictures) {
    Pictures init_pictures("../include/textures/amogus.png", "../include/textures/tnt.png");
    pictures = init_pictures;
}