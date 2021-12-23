#ifndef APPLICATION_INCLUDE_DANYA_CLIENT_H
#define APPLICATION_INCLUDE_DANYA_CLIENT_H

#include "model.h"
#include "player.h"
#include "wall.h"
#include "mob.h"
#include "map.h"

class Client {

private:
    sf::TcpSocket m_socket;
    sf::Packet m_packet;
    std::vector<Player> m_players;
    std::vector<Wall> m_unmovables;
    Mob m_mob;
    sf::RenderWindow m_window;
    Map m_map;
    sf::View m_camera;
    size_t m_id = -1;

public:
    Client();
    ~Client() = default;

};

#endif //APPLICATION_INCLUDE_DANYA_CLIENT_H
