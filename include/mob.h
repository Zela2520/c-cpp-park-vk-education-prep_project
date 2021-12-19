#ifndef APPLICATION_MOB_H
#define APPLICATION_MOB_H

#include "model.h"

class Mob : public Object {
public:
    Mob(float _x, float _y, const sf::Texture& texture);
    sf::Vector2<float> getPlayersCoords(Player player); //// получаем координаты объекта
    sf::Vector2<float> moveMob(Player player); //// задаём направление движения персонажу
    friend sf::Packet& operator << (sf::Packet& packet, const Mob& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Mob& unmovable);
    //sf::Player setTarget();
};

#endif //APPLICATION_MOB_H
