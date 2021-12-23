#ifndef INCLUDE_BULLET_H_
#define INCLUDE_BULLET_H_
#include "model.h"
#include "wall.h"



class Bullet : public Object {
    bool isAlive = false;
public:
    Bullet(float _x, float _y, float _rotation, const sf::Texture& texture);
    Bullet() = default;
    void move(float, float);
    friend sf::Packet& operator >> (sf::Packet& packet, Bullet& bullet);
    friend sf::Packet& operator << (sf::Packet& packet, const Bullet& bullet);
};



#endif // INCLUDE_BULLET_H_