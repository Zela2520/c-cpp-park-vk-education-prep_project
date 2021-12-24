#ifndef APPLICATION_INCLUDE_DANYA_SERVER_H
#define APPLICATION_INCLUDE_DANYA_SERVER_H

#include "mob.h"
#include "map.h"
#include "bullet.h"

#define ERROR (-1)

class Server {
public:
//    class Pictures {  //// Хранит в себе все текстурки
//    public:
//        Pictures() = default;
//        explicit Pictures(std::string amogus, std::string gachi) {
//            this->amogusTexture.loadFromFile(amogus);
//            this->gachiTexture.loadFromFile(gachi);
//        }
//
//        Pictures(const Server::Pictures& other_pictures) {
//            this->gachiTexture = other_pictures.gachiTexture;
//            this->amogusTexture = other_pictures.amogusTexture;
//        }
//
//        Pictures& operator=(const Pictures& other_pictures) {
//            this->gachiTexture = other_pictures.gachiTexture;
//            this->amogusTexture = other_pictures.amogusTexture;
//            return *this;
//        }
//        friend class Server;
//
//    private:
//        sf::Texture amogusTexture;
//        sf::Texture gachiTexture;
//    };
    sf::Texture amogusTexture;
    sf::Texture gachiTexture;
    sf::Texture globalWallTexture;
    sf::Texture localWallTexture;
    explicit Server(int port);
    void setConnection();
    void receiveClients();
    void sendData();
    void processAcquiredData();
    void startServer();

//    static void load_pictures(Pictures &pictures); //// если хотим добавить картинки необходимо прописать путт в этом методе

private:
    size_t port;
    int id = ERROR;
    sf::TcpListener listener;
//    sf::TcpSocket clientOne;
//    sf::TcpSocket clientTwo;
    std::vector<sf::TcpSocket>* clients;
    sf::Packet packet;

//    Pictures pictures;
    Map* map;
    std::vector<Player> players;
    std::vector<Bullet> bullets;
    sf::Clock moveTimer;
    sf::Clock reloadTimer;

};

#endif // APPLICATION_INCLUDE_DANYA_SERVER_H
