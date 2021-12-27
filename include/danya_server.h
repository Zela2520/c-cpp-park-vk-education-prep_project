#ifndef APPLICATION_INCLUDE_DANYA_SERVER_H
#define APPLICATION_INCLUDE_DANYA_SERVER_H

#include "mob.h"
#include "map.h"
#include "bullet.h"

#define ERROR (-1)
#define MOBS_SIZE (50)

class Server {
private:
    sf::Texture amogusTexture;
    sf::Texture gachiTexture;
    sf::Texture globalWallTexture;
    sf::Texture localWallTexture;
    sf::Texture pirateTexture;
    size_t port;
    double windowWidth = 500;
    double windowHeight = 500;
    sf::Vector2<float> spawnpoint;
    int amountOfKilled = 0;
    int id = ERROR;
    sf::TcpListener listener;
    std::vector<sf::TcpSocket>* clients;
    sf::Packet packet;

    Map* map;
    std::vector<Player> players;
    std::vector<Bullet> bullets;
    std::vector<Mob> mobs;
    sf::Clock moveTimer;
    sf::Clock newSpawnTimer;
    sf::Clock spawnrateTimer;

public:
    explicit Server(int port);
    void setConnection();
    void receiveClients();
    void sendData();
    void processAcquiredData();
    void startServer();
    bool badSpawn(Mob& mob);
    void checkMobSize();

};

#endif // APPLICATION_INCLUDE_DANYA_SERVER_H
