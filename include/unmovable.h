#ifndef APPLICATION_INCLUDE_OBJECT_H
#define APPLICATION_INCLUDE_OBJECT_H

#include "model.h"

class Wall : public Object {
public:
    Wall() = default;
    explicit Wall(const sf::RectangleShape &rectangle);
    Wall (float _x, float _y, const sf::Texture &texture);
    void draw(sf::RenderWindow& window) const;
    friend sf::Packet& operator << (sf::Packet& packet, const Wall& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Wall& unmovable);
};



#endif //APPLICATION_INCLUDE_OBJECT_H
