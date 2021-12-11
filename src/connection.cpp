#include "connection.h"
#include <cstdlib>

#define MAX_NUMBER_OF_CLIENTS 2

server_logic::Server::Server(size_t port) {
    m_port = port;
    m_number_of_clients = MAX_NUMBER_OF_CLIENTS;
}

void server_logic::Server::start_connection() {
    if (m_listener.listen(m_port) != sf::Socket::Done) {
        std::cerr << "the server is not ready to accept the client";
        exit(1);
    }

    this->set_clients_size();
    this->set_user_balls_size();
}

void server_logic::Server::receive_clients() {
    for (auto &socket : m_clients) {
        m_listener.accept(socket);
    }
}

void server_logic::Server::clients_init() {
    for (auto &cur_ball : m_user_balls) {
        cur_ball.x = 0;
        cur_ball.y = 0;
        cur_ball.color = "Black";
    }
}

void server_logic::Server::send_data() {
    for (int i = 0; i < m_clients.size(); ++i) {
        for (int j = 0; j < m_user_balls.size(); ++j) {
            m_packet << m_user_balls[j];
            m_clients[i].send(m_packet);
            m_packet.clear();
        }
    }
}

void server_logic::Server::clients_movements() {
    for (int i = 0; i < m_clients.size(); ++i) {
        // указывем направление движения объекта
        std::string dir = "\0";
        m_clients[i].receive(m_packet);
        m_packet >> dir;
        m_packet.clear();
        std::cout << dir << "\n";

        // обрабатываем действие пользователя
        if (dir == "UP") {
            --m_user_balls[i].y;
        }
        if (dir == "RIGHT") {
            ++m_user_balls[i].x;
        }
        if (dir == "DOWN") {
            ++m_user_balls[i].y;
        }
        if (dir == "LEFT") {
            --m_user_balls[i].x;
        }
    }
}

void server_logic::Server::start_server() {
    while (1) {
        this->clients_movements();
        this->send_data();
    }
}


void server_logic::Server::set_clients_size() {
    m_clients.reserve(m_number_of_clients);
}

void server_logic::Server::set_user_balls_size() {
    m_user_balls.reserve(m_number_of_clients);
}

