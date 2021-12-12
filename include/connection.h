#ifndef INCLUDE_CONNECTION_H_
#define INCLUDE_CONNECTION_H_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace server_logic {

    class Server {
    private:
        size_t m_port;
        sf::TcpListener m_listener;
        std::vector<sf::TcpSocket*> m_clients;
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
        void receive_clients();
        void clients_init();
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