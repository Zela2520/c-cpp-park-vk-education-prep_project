#ifndef APPLICATION_INCLUDE_DANYA_SERVER_H
#define APPLICATION_INCLUDE_DANYA_SERVER_H

#include "mob.h"
#include "map.h"

#define ERROR (-1)

class Server {
public:
    class Pictures {  //// Хранит в себе все текстурки
    public:
        Pictures() = default;
        explicit Pictures(std::string amogus, std::string gachi) {
            this->amogusTexture.loadFromFile(amogus);
            this->gachiTexture.loadFromFile(gachi);
        }

        Pictures(const Server::Pictures& other_pictures) {
            this->gachiTexture = other_pictures.gachiTexture;
            this->amogusTexture = other_pictures.amogusTexture;
        }

        Pictures& operator=(const Pictures& other_pictures) {
            this->gachiTexture = other_pictures.gachiTexture;
            this->amogusTexture = other_pictures.amogusTexture;
            return *this;
        }
        friend class Server;

    private:
        sf::Texture amogusTexture;
        sf::Texture gachiTexture;
    };
    explicit Server(size_t port);
    void set_connection();
    void receive_clients();
    void send_data();
    void clients_movements();
    void start_server();

    static void load_pictures(Pictures &pictures); //// если хотим добавить картинки необходимо прописать путт в этом методе

private:
    size_t m_port;
    int id = ERROR;
    sf::TcpListener m_listener;
    sf::TcpSocket m_client_one;
    sf::TcpSocket m_client_two;
    sf::Packet packet;

    Pictures m_pictures;
    Map* map;
    std::vector<Player> m_players;
    sf::Clock m_clock;

};

#endif // APPLICATION_INCLUDE_DANYA_SERVER_H
