#ifndef INCLUDE_CONNECTION_H_
#define INCLUDE_CONNECTION_H_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace server_logic {

    class Server {
    private:
        size_t m_port;
        size_t m_number_of_clients;
        sf::TcpListener m_listener;
        std::vector<std::unique_ptr<sf::TcpSocket>> m_clients;
        sf::Packet m_packet;
        struct Ball {
            int x;
            int y;
            std::string color;
        };
        std::vector<Ball> m_user_balls;

    public:

        Server(size_t port);
        ~Server() = default;
        void set_connection();
        void set_clients_size();
        void receive_clients();
        void clients_init();
        void set_user_balls_size();
        void send_data();
        void clients_movements();
        void start_server();

        friend sf::Packet& operator<<(sf::Packet& packet, const Ball& ball) {
            return packet << ball.x << ball.y << ball.color;
        }
        friend sf::Packet& operator>>(sf::Packet& packet, Ball& ball) {
            return packet >> ball.x >> ball.y >> ball.color;
        }
    };
}

#endif  // INCLUDE_CONNECTION_H_