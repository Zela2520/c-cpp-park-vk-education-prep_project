#include "../../include/unmovable.h"


Wall::Wall(const sf::RectangleShape &rectangle) {
    const sf::Texture* temp_texture = rectangle.getTexture();
    sprite.setTexture(*temp_texture);
    sf::Vector2f rectangle_coord = rectangle.getSize();
    setX(rectangle_coord.x);
    setY(rectangle_coord.y);
}

Wall::Wall(float _x, float _y, const sf::Texture& texture) : Object() {
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
    setX(_x);
    setY(_y);
}

void Wall::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
}

sf::Packet& operator >> (sf::Packet& packet, Wall& unmovable) {  //// Пакета в статичный объект
    float x, y;
    packet >> x >> y;
    unmovable.setX(x);
    unmovable.setY(y);
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const Wall& unmovable) {  //// Из статичного объекта в пакет
    return packet << unmovable.getX() << unmovable.getY();
}


