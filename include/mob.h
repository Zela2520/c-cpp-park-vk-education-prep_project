#ifndef APPLICATION_MOB_H
#define APPLICATION_MOB_H

#include "player.h"

class Mob : public Object {
public:
    Mob() = default;
    Mob(float _x, float _y, const sf::Texture& texture);
    sf::Vector2<float> getPlayersCoords(Player player); //// получаем координаты игрока
    sf::Vector2<float> moveMob(Player player, std::vector<Wall> walls); //// задаём направление движения персонажу
    Player& setTaregt(std::vector<Player>& players);
    bool intersectsWith(std::vector<Wall>& objects);
//    void moveMobeX(std::vector<Wall> &walls);
//    void moveMobeY(std::vector<Wall> &walls);
    friend sf::Packet& operator << (sf::Packet& packet, const Mob& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Mob& unmovable);
    //sf::Player setTarget();
};

#endif //APPLICATION_MOB_H
