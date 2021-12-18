#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace sf;
using namespace std;

#ifndef PROJECT_INCLUDE_MODEL_H_
#define PROJECT_INCLUDE_MODEL_H_

class Object {
protected:
    float x = 0;
    float y = 0;
    float defaultWidth = -1;
    float defaultHeight = -1;
    float xScale = 1;
    float yScale = 1;
    float rotation = 0;
    Sprite sprite;
    bool turnedRight = true;
//    Texture texture;
public:
    Sprite getSprite() const;
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    float getRotation() const;
    float getXScale() const;
    float getYScale() const;
    void setScale(float _x, float _y);
    void setX(float _x);
    void setY(float _y);
    void move(float _x, float _y);
    void setRotation(float _rotation);
    void setTurnedRight(bool _turnedRight);
    void goUp(float distance = 1);
    void goDown(float distance = 1);
    void goRight(float distance = 1);
    void goLeft(float distance = 1);
    virtual void draw(RenderWindow& window);
//    virtual bool intersectsWith(vector<Object>& objects);
};

class Unmovable : public Object {
private:
public:
    Unmovable(float _x, float _y, const Texture &texture);
//    Unmovable(float _x, float _y);
    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable);
};

class Player : public Object {
    int Id = -1;
public:
    Player(float _x, float _y, const Texture& texture);
    Player() = default;
//    Player(float _x, float _y);
    bool intersectsWith(vector<Unmovable>& objects);
    void draw(RenderWindow& window) override;
    void setId(int);
    int getId() const;
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
};

class Turret : public Object {
public:
    Turret(float _x, float _y, const Texture& texture);
    Player& getClosestPlayer(vector<Player>& players) const;
    float getDirection(Player& player) const;
    friend sf::Packet& operator >> (sf::Packet& packet, Turret& turret);
    friend sf::Packet& operator << (sf::Packet& packet, const Turret& turret);
};

class Bullet : public Object {
    bool isAlive = false;
public:
    Bullet(float _x, float _y, float _rotation, const Texture& texture);
    friend sf::Packet& operator >> (sf::Packet& packet, Bullet& bullet);
    friend sf::Packet& operator << (sf::Packet& packet, const Bullet& bullet);
};

double sqr(double n);

float getDirection(Player& player);

Packet& operator >> (sf::Packet& packet, bool* directions);
Packet& operator << (sf::Packet& packet, const bool* directions);




#endif // PROJECT_INCLUDE_MODEL_H_
