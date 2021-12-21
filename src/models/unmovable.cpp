#include "../../include/unmovable.h"


Unmovable::Unmovable(const sf::RectangleShape &rectangle) {
    const sf::Texture* temp_texture = rectangle.getTexture();
    sprite.setTexture(*temp_texture);
    sf::Vector2f rectangle_coord = rectangle.getSize();
    setX(rectangle_coord.x);
    setY(rectangle_coord.y);
}

//Unmovable::Unmovable(float _x, float _y, const sf::Texture& texture) : Object() {
//    sprite.setTexture(texture);
//    setX(_x);
//    setY(_y);
//}

sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable) {  //// Пакета в статичный объект
    float x, y;
    packet >> x >> y;
    unmovable.setX(x);
    unmovable.setY(y);
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable) {  //// Из статичного объекта в пакет
    return packet << unmovable.getX() << unmovable.getY();
}


