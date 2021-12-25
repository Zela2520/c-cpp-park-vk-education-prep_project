#ifndef PROJECT_INCLUDE_MODEL_H_
#define PROJECT_INCLUDE_MODEL_H_


#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <string>

#include "cmath"


class Object {

protected:
    float x = 0;
    float y = 0;
    float defaultWidth = -1;
    float defaultHeight = -1;
    float xScale = 1;
    float yScale = 1;
    float rotation = 0;
    sf::Sprite sprite;
    bool turnedRight = true;
    sf::Texture m_texture;

public:

    sf::Sprite getSprite() const;
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
    virtual void draw(sf::RenderWindow& window);
};

sf::Packet& operator >> (sf::Packet& packet, bool* directions);
sf::Packet& operator << (sf::Packet& packet, const bool* directions);
//sf::Packet& operator << (sf::Packet& packet, bool& isLMBPressed);
//sf::Packet& operator >> (sf::Packet& packet, bool& isLMBPressed);

float getAngle(double x, double y, double, double);


#endif // PROJECT_INCLUDE_MODEL_H_