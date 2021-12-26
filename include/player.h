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
    int isInvincible = false;
    int amountOfKilledMobs = 0;
    sf::Clock invincibilityTimer;
public:
    Player(float _x, float _y, const sf::Texture& texture);
    bool intersectsWith(std::vector<Wall>& objects);
//    bool intersectsWith(std::vector<localBound>& objects);
//    bool intersectsWith(std::vector<globalBound>& objects);
    void draw(sf::RenderWindow& window) override;
    void setId(int);
    void increaseAmountOfKilledMobs(int amount);
    int getAmountOfKilledMobs() const;
    int getId() const;
    bool getInvincibility() const;
    float getElapsedInvincibilityTime() const;
    void resetInvincibilityTimer();
    void setInvincibility(bool);
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
};

#endif //APPLICATION_INCLUDE_PLAYER_H
