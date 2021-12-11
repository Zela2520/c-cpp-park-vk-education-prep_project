#include "connection.h"
#include <cstdlib>

#define MAX_NUMBER_OF_CLIENTS 2

server_logic::Server::Server(size_t port) {
    m_port = port;
    m_number_of_clients = MAX_NUMBER_OF_CLIENTS;
    std::cout << "Server was started\n";
}

void server_logic::Server::set_connection() {
    std::cout << "Сервер должен начать слушать\n";
    if (m_listener.listen(m_port) != sf::Socket::Done) {
        std::cerr << "the server is not ready to accept the client";
        exit(1);
    }

    std::cout << "Сервер начал слушать\n";
    this->set_clients_size();
    this->set_user_balls_size();
}

void server_logic::Server::receive_clients() {
    std::cout << "Сервер должен принять клиента\n";
    for (auto &client : m_clients) {
        m_listener.accept(*client);
        std::cout << "Сервер принял клиента\n";
    }
}

void server_logic::Server::clients_init() {
    std::cout << " КЛИЕНТ ДОЛЖЕН БЫТЬ ИНИЦИЛИЗИРОВАН\n";
    for (auto &cur_ball : m_user_balls) {
        cur_ball.x = 0;
        cur_ball.y = 0;
        cur_ball.color = "Black";
        std::cout << " КЛИЕНТ ИНИЦИАЛИЗИРОВАН\n";
    }
}

void server_logic::Server::send_data() {
    std::cout << "ДАННЫЕ ДОЛЖНЫ БЫТЬ ОТПРАВЛЕНЫ\n";
    for (int i = 0; i < m_clients.size(); ++i) {
        for (int j = 0; j < m_user_balls.size(); ++j) {
            m_packet << m_user_balls[j];
            m_clients[i]->send(m_packet);
            m_packet.clear();
            std::cout << "ДАННЫЕ БЫЛИ ОТПРАВЛЕНЫ\n";
        }
    }
}

void server_logic::Server::clients_movements() {
    std::cout << "НАЧИНАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
    for (int i = 0; i < m_clients.size(); ++i) {
        // указывем направление движения объекта
        std::string dir = "\0";
        m_clients[i]->receive(m_packet);
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
    std::cout << "ЗАКАНЧИВАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
}

void server_logic::Server::start_server() {
    std::cout << "СТАРТ";
    while (1) {
        this->clients_movements();
        this->send_data();
    }
    std::cout << "";
}


void server_logic::Server::set_clients_size() {
    std::cout << "УСТАНВЛИВАЕМ РАЗМЕР\n";
    m_clients.reserve(m_number_of_clients);
}

void server_logic::Server::set_user_balls_size() {
    std::cout << "УСТАНВЛИВАЕМ РАЗМЕР\n";
    m_user_balls.reserve(m_number_of_clients);
}

