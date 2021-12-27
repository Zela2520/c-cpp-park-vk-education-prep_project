#include "../../include/bullet.h"

Bullet::Bullet(float _x, float _y, float _rotation, const sf::Texture& texture) {
    sprite.setTexture(texture);
    setX(_x);
    setY(_y);
    setRotation(_rotation);
    defaultWidth = sprite.getGlobalBounds().width;
    defaultHeight = sprite.getGlobalBounds().height;
    setScale(0.5, 0.2);
    isAlive = true;
}

void Bullet::move(float _x, float _y) {
    setX(x + _x);
    setY(y + _y);
}

sf::Packet& operator >> (sf::Packet& packet, Bullet& bullet) {
    float x, y, rotation;
    packet >> x >> y >> rotation;
    bullet.setX(x);
    bullet.setY(y);
    bullet.setRotation(rotation);
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const Bullet& bullet) {
    return packet << bullet.getX() << bullet.getY() << bullet.getRotation();
}