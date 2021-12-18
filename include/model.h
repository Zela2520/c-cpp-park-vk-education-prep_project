#ifndef PROJECT_INCLUDE_MODEL_H_
#define PROJECT_INCLUDE_MODEL_H_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace sf;
using namespace std;

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
    Texture m_texture;
public:
    void setSprite();
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
    void setRotation(float _rotation);
    void setTurnedRight(bool _turnedRight);
    void goUp(float distance = 1);
    void goDown(float distance = 1);
    void goRight(float distance = 1);
    void goLeft(float distance = 1);
    void load_picture(std::string path_to_file);
    virtual void draw(RenderWindow& window);
};

class Unmovable : public Object {
private:
public:
    Unmovable(float _x, float _y, const Texture &texture);
    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable);
};

class Player : public Object {
    int Id = -1;
public:
    Player(float _x, float _y, const Texture& texture);
    bool intersectsWith(vector<Unmovable>& objects);
    void draw(RenderWindow& window) override;
    void setId(int);
    int getId() const;
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
};

class Mob : public Object {
public:
    sf::Vector2<float> getPlayersCoords(Player player); //// получаем координаты объекта
    sf::Vector2<float> moveMob(Mob mob, Player player); //// задаём направление движения персонажу
    friend sf::Packet& operator << (sf::Packet& packet, const Mob& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Mob& unmovable);
    //sf::Player setTarget();
};

Packet& operator >> (sf::Packet& packet, bool* directions);
Packet& operator << (sf::Packet& packet, const bool* directions);




#endif // PROJECT_INCLUDE_MODEL_H_