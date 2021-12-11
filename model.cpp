#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "model.h"
using namespace sf;
using namespace std;

Sprite Object::getSprite() const {
    return sprite;
}
float Object::getX() const {
    return sprite.getPosition().x;
}
float Object::getY() const {
    return sprite.getPosition().y;
}
float Object::getRotation() const {
    return sprite.getRotation();
}
void Object::setX(float _x) {
    sprite.setPosition(_x, this->getY());
}
void Object::setY(float _y) {
    sprite.setPosition(this->getX(), _y);
}
void Object::setRotation(float _rotation) {
    sprite.setRotation(_rotation);
}
void Object::setTurnedRight(bool _turnedRight) {
    turnedRight = _turnedRight;
}
void Object::goUp(float distance) {
    sprite.setPosition(this->getX(), this->getY() - distance);
}
void Object::goDown(float distance) {
    sprite.setPosition(this->getX(), this->getY() + distance);
}
void Object::goRight(float distance) {
    sprite.setPosition(this->getX() + distance, this->getY());
//    sprite.rotate(180);
    turnedRight = true;
}
void Object::goLeft(float distance) {
    sprite.setPosition(this->getX() - distance, this->getY());
//    sprite.setTextureRect(IntRect(getX() + sprite.getGlobalBounds().width, getY(), -sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    turnedRight = false;
//    sprite.rotate(180);
//    sprite.move(-this->getX(), -this->getY());
}
void Object::draw(RenderWindow& window) {
//    if (turnedRight) {
//        sprite.setTextureRect(IntRect(getX(), getY(), sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
//    } else if (!turnedRight) {
//        sprite.setTextureRect(IntRect(getX() + sprite.getGlobalBounds().width, getY(), -sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
//    }
    window.draw(sprite);
    window.draw(border);
}

Unmovable::Unmovable(float _x, float _y, const Texture& texture) : Object() {
    sprite.setTexture(texture);
//        sprite.setColor(Color(0, 255, 0));
//        sprite.setColor(Color(100,255,100, 100));
    this->setX(_x);
    this->setY(_y);
}
//Unmovable::Unmovable(float _x, float _y) {
//    this->setX(_x);
//    this->setY(_y);
//}

Player::Player(float _x, float _y, const Texture& texture) : Object() {
    sprite.setTexture(texture);
//    if (turnedRight) {
//        sprite.setTextureRect(IntRect(getX(), getY(), sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
//        cout << "ПРАВАК" << endl;
//    }
//    if (!turnedRight) {
//        cout << "Левак!" << endl;
//        sprite.setTextureRect(IntRect(getX() + sprite.getGlobalBounds().width, getY(), -sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
//    }
    sprite.setScale(0.1, 0.1);  // Масштабировани модели
    this->setX(_x);
    this->setY(_y);
}
//Player::Player(float _x, float _y) : Object() {
//    sprite.scale(1, 1);  // Масштабировани модели
//    this->setX(_x);
//    this->setY(_y);
//}
bool Player::intersectsWith(vector<Unmovable>& objects) {
    for (auto& object : objects) {
        Rect<float> thisBounds = sprite.getGlobalBounds();
        Rect<float> objectBounds = object.getSprite().getGlobalBounds();

        if (thisBounds.intersects((objectBounds))) {
            std::cout << "ПЕРЕСЕЧЕНИЕ" << endl;
            cout << "Масштаб" << sprite.getScale().x << "*" << thisBounds.width << endl;
            cout << thisBounds.left << " " << thisBounds.top << " " << thisBounds.height << " " << thisBounds.width << endl;
            cout << objectBounds.left << " " << objectBounds.top << " " << objectBounds.height << " " << objectBounds.width << endl;
            return true;
        } else {
            cout << "НЕТ ПЕРЕСЕЧЕНИЯ" << endl;
            cout << thisBounds.left << " " << thisBounds.top << " " << thisBounds.height << " " << thisBounds.width << endl;
            cout << objectBounds.left << " " << objectBounds.top << " " << objectBounds.height << " " << objectBounds.width << endl;
        }
    }
    return false;
}
void Player::draw(RenderWindow& window) {
    cout << "Я НУЖНЫЙ КОНСТРУКТОР" << endl;
    sprite.setScale(1, 1);
    if (turnedRight) {
        sprite.setTextureRect(IntRect(getX(), getY(), sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
        cout << "ПРАВАК" << endl;
    } else if (!turnedRight) {
        cout << "Левак!" << endl;
        sprite.setTextureRect(IntRect(getX() + sprite.getGlobalBounds().width, getY(), -sprite.getGlobalBounds().width,sprite.getGlobalBounds().height));
    }
    sprite.setScale(0.1, 0.1);
    window.draw(sprite);
    window.draw(border);
}



sf::Packet& operator << (sf::Packet& packet, const Player& player) {  // Из игрока в пакет
    return packet << player.getX() << player.getY() << player.turnedRight;
}
sf::Packet& operator >> (sf::Packet& packet, Player& player) {  // Из пакета в игрока
    float x, y;
    bool turnedRight;
    packet >> x >> y >> turnedRight;
    player.setTurnedRight(turnedRight);
    player.setX(x);
    player.setY(y);
//    if (angle == 0) {
//        sprite.setTextureRect(IntRect(getX(), getY(), sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
//    }
//    player.setRotation(angle);
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const bool* directions) {  // Из массива направлений в пакет
    return packet << directions[0] << directions[1] << directions[2] << directions[3];
}
sf::Packet& operator >> (sf::Packet& packet, bool* directions) {  // Из пакета в массив направлений
    return packet >> directions[0] >> directions[1] >> directions[2] >> directions[3];
}

sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable) {  // Пакета в статичный объект
    float x, y;
    packet >> x >> y;
    unmovable.setX(x);
    unmovable.setY(y);
    return packet;
}
sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable) {  // Из статичного объекта в пакет
    return packet << unmovable.getX() << unmovable.getY();
}