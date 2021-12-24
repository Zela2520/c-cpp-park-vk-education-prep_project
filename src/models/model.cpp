#include "../../include/model.h"


sf::Sprite Object::getSprite() const {
    return sprite;
}

float Object::getX() const {
    return x;
}

float Object::getY() const {
    return y;
}

float Object::getWidth() const {
    return defaultWidth;
}

float Object::getHeight() const {
    return defaultHeight;
}

float Object::getRotation() const {
    return rotation;
}

float Object::getXScale() const {
    return xScale;
}

float Object::getYScale() const {
    return yScale;
}

void Object::setX(float _x) {
    x = _x;
    sprite.setPosition(_x, y);
}

void Object::setY(float _y) {
    y = _y;
    sprite.setPosition(x, _y);
}

void Object::setRotation(float _rotation) {
    rotation = _rotation;
    sprite.setRotation(rotation);
}

void Object::setTurnedRight(bool _turnedRight) {
    turnedRight = _turnedRight;
}

void Object::setScale(float _xScale, float _yScale) {
    xScale = _xScale;
    yScale = _yScale;
    sprite.setScale(_xScale, _yScale);
}

void Object::goUp(float distance) {
    y -= distance;
    sprite.move(0, -distance);
}

void Object::goDown(float distance) {
    y += distance;
    sprite.move(0, distance);
}

void Object::goRight(float distance) {
    x += distance;
    sprite.move(distance, 0);
    turnedRight = true;
}

void Object::goLeft(float distance) {
    x -= distance;
    sprite.move(-distance, 0);
    turnedRight = false;
}

void Object::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Object::load_picture(std::string path_to_file) {
    m_texture.loadFromFile(path_to_file);
}


sf::Packet& operator << (sf::Packet& packet, const bool* directions) {  //// Из массива направлений в пакет
    return packet << directions[0] << directions[1] << directions[2] << directions[3];
}

sf::Packet& operator >> (sf::Packet& packet, bool* directions) {  //// Из пакета в массив направлений
    return packet >> directions[0] >> directions[1] >> directions[2] >> directions[3];
}
//
//sf::Packet& operator << (sf::Packet& packet, bool& isLMBPressed) {  //// Из пакета в массив направлений
//    return packet << isLMBPressed;
//}
//
//sf::Packet& operator >> (sf::Packet& packet, bool& isLMBPressed) {  //// Из пакета в массив направлений
//    return packet >> isLMBPressed;
//}

float getAngle(int x, int y) {
    if (x > 250 && y > 250) {
        return 180/3.1415 * atan(fabs(y - 250)/fabs(x - 250));
    }
    if (x < 250 && y > 250) {
        return 180 - 180/3.1415 * atan(fabs(y - 250)/fabs(x - 250));
    }
    if (x > 250 && y < 250) {
        return -180/3.1415 * atan(fabs(y - 250)/fabs(x - 250));
    }
    if (x < 250 && y < 250) {
        return 180 + 180/3.1415 * atan(fabs(y - 250)/fabs(x - 250));
    }
}
