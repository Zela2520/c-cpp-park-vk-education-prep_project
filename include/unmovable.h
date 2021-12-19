#ifndef APPLICATION_INCLUDE_OBJECT_H
#define APPLICATION_INCLUDE_OBJECT_H

#include "model.h"

class Unmovable : public Object {
public:
    Unmovable(float _x, float _y, const sf::Texture &texture);
    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable);
};



#endif //APPLICATION_INCLUDE_OBJECT_H
