#include "../../include/danya_server.h"
#include <iostream>

#define MAX_NUMBER_OF_CLIENTS 2
#define INIT_ID 1


Server::Server(size_t port) {
    m_port = port;
    load_pictures(m_pictures);
    m_map.creat_map(m_unmovables, &m_pictures.gachiTexture); //// можно передавать несколько текстур, чтобы объекты были разные либо передавать Pictures&, а в map подключить server_danya.h
    for (int i = 0; i < MAX_NUMBER_OF_CLIENTS; i++) {
        m_players.emplace_back(20, 30, m_pictures.amogusTexture);
        m_players[i].setId(i);
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

    m_id = INIT_ID;
    m_packet << m_id;
    m_client_one.send(m_packet);
    m_packet.clear();
    ++m_id;

    if (m_listener.accept(m_client_two) != sf::Socket::Done) {
        std::cerr << "The server is not ready to accept the client";
        exit(1);
    }

    m_packet << m_id;
    m_client_two.send(m_packet);
    m_packet.clear();
    std::cout << "Сервер принял клиентов\n";
}

void Server::send_data() {
    std::cout << "ДАННЫЕ ДОЛЖНЫ БЫТЬ ОТПРАВЛЕНЫ\n";

    //// кусок ниже можно сделать ассинхроно, добавив функцию void и передавая в неё нужного клиента.

    //// Отправляем данные первому клиенту
    for (auto& cur_player : m_players) {
        m_packet << cur_player;
        m_client_one.send(m_packet);
        m_packet.clear();
        std::cout << "ДАННЫЕ БЫЛИ ОТПРАВЛЕНЫ\n";
    }
    for (auto& unmovable : m_unmovables) {   //// И о каждом несдвигаемом объекте.
        m_packet << unmovable;
        m_client_one.send(m_packet);
        m_packet.clear();
    }

    //// Отправляем данные второму клиенту
    for (auto& cur_player : m_players) {
        m_packet << cur_player;
        m_client_two.send(m_packet);
        m_packet.clear();
        std::cout << "ДАННЫЕ БЫЛИ ОТПРАВЛЕНЫ\n";
    }
    for (auto& unmovable : m_unmovables) {   //// И о каждом несдвигаемом объекте.
        m_packet << unmovable;
        m_client_two.send(m_packet);
        m_packet.clear();
    }
}

void Server::clients_movements() {
    std::cout << "НАЧИНАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
    float time = m_clock.getElapsedTime().asMicroseconds();
    m_clock.restart();
    time /= 400;
    m_client_one.receive(m_packet);
    bool directions[4];
    m_packet >> directions;  //// Достаём информацию из пакета.
    m_packet.clear();

    //// Обрабатываем полученную информацию о направлении.
    if (directions[0]) {   //// Вверх.
        m_players[0].goUp(0.3 * time);
        if (m_players[0].intersectsWith(m_unmovables)) m_players[0].goDown(0.3 * time);
    }
    if (directions[1]) {  //// Направо.
        m_players[0].goRight(0.3 * time);
        if (m_players[0].intersectsWith(m_unmovables)) m_players[0].goLeft(0.3 * time);
    }
    if (directions[2]) {  //// Вниз.
        m_players[0].goDown(0.3 * time);
        if (m_players[0].intersectsWith(m_unmovables)) m_players[0].goUp(0.3 * time);
    }
    if (directions[3]) {  //// Налево.
        m_players[0].goLeft(0.3 * time);
        if (m_players[0].intersectsWith(m_unmovables)) m_players[0].goRight(0.3 * time);
    }

    m_client_two.receive(m_packet);
    m_packet >> directions;  //// Достаём информацию из пакета.
    m_packet.clear();

    //// Обрабатываем полученную информацию о направлении.
    if (directions[0]) {   //// Вверх.
        m_players[1].goUp(0.3 * time);
        if (m_players[1].intersectsWith(m_unmovables)) m_players[1].goDown(0.3 * time);
    }
    if (directions[1]) {  //// Направо.
        m_players[1].goRight(0.3 * time);
        if (m_players[1].intersectsWith(m_unmovables)) m_players[1].goLeft(0.3 * time);
    }
    if (directions[2]) {  //// Вниз.
        m_players[1].goDown(0.3 * time);
        if (m_players[1].intersectsWith(m_unmovables)) m_players[1].goUp(0.3 * time);
    }
    if (directions[3]) {  //// Налево.
        m_players[1].goLeft(0.3 * time);
        if (m_players[1].intersectsWith(m_unmovables)) m_players[1].goRight(0.3 * time);
    }

    std::cout << "ЗАКАНЧИВАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
}

void Server::start_server() {
    std::cout << "СТАРТ";
    while (1) {
        clients_movements();
        std::cout << "ДАННЫЕ ДОЛЖНЫ УЛЕТЕТЬ КЛИЕНТУ";
        send_data();
        std::cout << "ДАННЫЕ УЛЕТЕЛИ КЛИЕНТУ";
    }
}

void Server::load_pictures(Pictures &pictures) {
    Pictures init_pictures("../include/textures/amogus.png", "../include/textures/gachi.png");
    pictures = init_pictures;
}