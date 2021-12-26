#ifndef APPLICATION_INCLUDE_DANYA_CLIENT_H
#define APPLICATION_INCLUDE_DANYA_CLIENT_H

#include "model.h"
#include "player.h"
#include "wall.h"
#include "mob.h"
#include "map.h"

class Client {

public:
    explicit Client(size_t port);
    ~Client() = default;
    void setConnection();
    void receiveData();
    void sendData();

private:
    size_t port;
    sf::TcpSocket socket;
    sf::Packet packet;
    std::vector<Player> players;
    std::vector<Wall> unmovables;
    Mob mob;
    sf::RenderWindow window;
    Map map;
    sf::View camera;
    size_t id = -1;



};

#endif //APPLICATION_INCLUDE_DANYA_CLIENT_H
