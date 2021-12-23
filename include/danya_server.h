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
    explicit Server(int port);
    void set_connection();
    void receive_clients();
    void send_data();
    void clients_movements();
    void start_server();

    static void load_pictures(Pictures &pictures); //// если хотим добавить картинки необходимо прописать путт в этом методе

private:
    size_t port;
    int id = ERROR;
    sf::TcpListener listener;
    sf::TcpSocket clientOne;
    sf::TcpSocket clientTwo;
    sf::Packet packet;

    Pictures pictures;
    Map* map;
    std::vector<Player> players;
    sf::Clock clock;

};

#endif // APPLICATION_INCLUDE_DANYA_SERVER_H
