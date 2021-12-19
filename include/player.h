#ifndef APPLICATION_INCLUDE_PLAYER_H
#define APPLICATION_INCLUDE_PLAYER_H

#include "model.h"

class Player : public Object {
    int Id = -1;
public:
    Player(float _x, float _y, const sf::Texture& texture);
    bool intersectsWith(std::vector<Unmovable>& objects);
    void draw(sf::RenderWindow& window) override;
    void setId(int);
    int getId() const;
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
};

#endif //APPLICATION_INCLUDE_PLAYER_H
