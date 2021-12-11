#include "connection.h"

using namespace sf;
using namespace std;

#ifndef INCLUDE_MODEL_H_
#define INCLUDE_MODEL_H_

class Object {
protected:

    CircleShape border;
    Sprite sprite;

public:
    Sprite& getSprite();
    float getX() const;
    float getY() const;
    void setX(float _x);
    void setY(float _y);
    void goUp(float distance = 1);
    void goDown(float distance = 1);
    void goRight(float distance = 1);
    void goLeft(float distance = 1);
    void draw(RenderWindow& window);

    friend server_logic::Server;
};

class Unmovable : public Object {
private:
public:
    Unmovable(float _x, float _y, const Texture &texture);
    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable);
    friend server_logic::Server;
};

class Player : public Object {
public:
    Player(float _x, float _y, const Texture& texture);
    bool intersectsWith(vector<Unmovable>& objects);
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
    friend server_logic::Server;
};

Packet& operator >> (sf::Packet& packet, bool* directions);
Packet& operator << (sf::Packet& packet, const bool* directions);


#endif // INCLUDE_MODEL_H_