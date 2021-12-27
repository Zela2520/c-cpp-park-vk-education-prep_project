#ifndef APPLICATION_INCLUDE_PLAYER_H
#define APPLICATION_INCLUDE_PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <string>

#include "wall.h"
#include "cmath"


class Player : public Object {
    int id = -1;
public:
    Player(float _x, float _y, const sf::Texture& texture);
    bool intersectsWith(std::vector<Wall>& objects);
    void draw(sf::RenderWindow& window) override;
    void setId(int);
    int getId() const;
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
};

#endif //APPLICATION_INCLUDE_PLAYER_H
