#include "../../include/connection.h"

#define MAX_NUMBER_OF_CLIENTS 2

server_logic::Server::Server(size_t port) {
    m_port = port;
    std::cout << "Server was started\n";
}

void server_logic::Server::set_connection() {
    std::cout << "Сервер должен начать слушать\n";

    if (m_listener.listen(m_port) != sf::Socket::Done) {
        std::cerr << "The server is not ready to accept the client";
        exit(1);
    }

    std::cout << "Сервер начал слушать\n";
}

void server_logic::Server::receive_clients() {
    std::cout << "Сервер должен принять клиента\n";
    std::vector<sf::TcpSocket> for_users(MAX_NUMBER_OF_CLIENTS);
    for (auto &cur_client : for_users) {
        if (m_listener.accept(cur_client) != sf::Socket::Done) {
            std::cerr << "The server is not ready to accept the client";
            exit(1);
        }
        m_clients.push_back(&cur_client);
    }
    std::cout << "Сервер принял клиента\n";
}

void server_logic::Server::clients_init() {
    std::cout << " КЛИЕНТ ДОЛЖЕН БЫТЬ ИНИЦИЛИЗИРОВАН\n";
    Ball cur_ball{0, 0,"Black"};
    size_t count = 0;
    while (count < MAX_NUMBER_OF_CLIENTS) {
        m_user_balls.emplace_back(cur_ball);
        ++count;
    }
    std::cout << " КЛИЕНТ ИНИЦИАЛИЗИРОВАН\n";
}

void server_logic::Server::send_data() {
    std::cout << "ДАННЫЕ ДОЛЖНЫ БЫТЬ ОТПРАВЛЕНЫ\n";
    for (auto& cur_client : m_clients) {
        for (auto& cur_ball : m_user_balls) {
            m_packet << cur_ball;
            cur_client->send(m_packet);
            m_packet.clear();
            std::cout << "ДАННЫЕ БЫЛИ ОТПРАВЛЕНЫ\n";
        }
    }
}

void server_logic::Server::clients_movements() {
    std::cout << "НАЧИНАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
    for (int i = 0; i < m_user_balls.size(); ++i) {
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
        std::cout << " information has been received\n";
    }
    std::cout << "ЗАКАНЧИВАЕМ ОТСЛЕЖИВАТЬ ПЕРЕДВИЖЕНИЯ КЛИЕНТА\n";
}

void server_logic::Server::start_server() {
    std::cout << "СТАРТ";
    while (1) {
        clients_movements();
        std::cout << "ДАННЫЕ ДОЛЖНЫ УЛЕТЕТЬ КЛИЕНТУ";
        send_data();
        std::cout << "ДАННЫЕ УЛЕТЕЛИ КЛИЕНТУ";
    }
}

