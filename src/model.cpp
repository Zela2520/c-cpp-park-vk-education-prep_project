#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "../include/model.h"
#include "cmath"

using namespace sf;
using namespace std;


Sprite Object::getSprite() const {
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
void Object::draw(RenderWindow& window) {
    //this->sprite.setTexture(m_texture);
    window.draw(sprite);
}

void Object::load_picture(std::string const path_to_file) {
    m_texture.loadFromFile(path_to_file);
}




Unmovable::Unmovable(float _x, float _y, const Texture& texture) : Object() {
    sprite.setTexture(texture);
    setX(_x);
    setY(_y);
}

Mob::Mob(float _x, float _y, const Texture& texture) {
    sprite.setTexture(texture);
    setX(_x);
    setY(_y);
}
Player::Player(float _x, float _y, const Texture& _texture) : Object() {  //// Конструктор инициализации игрока.
    sprite.setTexture(_texture);
    defaultWidth = sprite.getGlobalBounds().width;
    defaultHeight = sprite.getGlobalBounds().height;
    setScale(0.1, 0.1);  //// Масштабировани модели
    setX(_x);
    setY(_y);
}

bool Player::intersectsWith(vector<Unmovable>& objects) {
    for (auto& object : objects) {
        Rect<float> thisBounds = sprite.getGlobalBounds();
        Rect<float> objectBounds = object.getSprite().getGlobalBounds();

        return (thisBounds.intersects(objectBounds));
    }
    return false;
}

void Player::draw(RenderWindow& window) {
    cout << "Дефолтные размеры " << defaultWidth << "x" << defaultHeight << endl;
    if (turnedRight) {
        sprite.setTextureRect(IntRect(0, 0, (int)defaultWidth, (int)defaultHeight));
    }
    if (!turnedRight) {
        sprite.setTextureRect(IntRect(0 + (int)defaultWidth, 0, - (int)defaultWidth,(int)defaultHeight));
    }
//    sprite.setScale(scale, scale);
    window.draw(sprite);
}

void Player::setId(int _gotId) {
    Id = _gotId;
}

int Player::getId() const {
    return Id;
}

Vector2<float> Mob::getPlayersCoords(const Player player) {
    Vector2<float> playersCoords(player.getX(), player.getY());
    return playersCoords;
}

Vector2<float> Mob::moveMob(Player player) {
    Vector2<float> playersCoords = getPlayersCoords(player);
    Vector2<float> mobCoords(this->getX(), this->getY());
    Vector2<float> movingDir(playersCoords.x - mobCoords.x, playersCoords.y - mobCoords.y);
    movingDir.x /= static_cast<float>(pow(pow(playersCoords.x - mobCoords.x, 2) + pow(playersCoords.y - mobCoords.y, 2), 0.5));
    movingDir.y /= static_cast<float>(pow(pow(playersCoords.x - mobCoords.x, 2) + pow(playersCoords.y - mobCoords.y, 2), 0.5));
    this->setX(movingDir.x + this->getX());
    this->setY(movingDir.y + this->getY());
    return movingDir;
}



sf::Packet& operator << (sf::Packet& packet, const Player& player) {  //// Из игрока в пакет
    return packet << player.getId() << player.getX() << player.getY() << player.turnedRight;
}
sf::Packet& operator >> (sf::Packet& packet, Player& player) {  //// Из пакета в игрока
    float x, y;
    int Id;
    bool turnedRight;
    packet >> Id >> x >> y >> turnedRight;
    player.setTurnedRight(turnedRight);
    player.setX(x);
    player.setY(y);
    player.setId(Id);

    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const Mob& player) {  //// Из игрока в пакет
    return packet << player.getX() << player.getY() << player.turnedRight;
}

sf::Packet& operator >> (sf::Packet& packet, Mob& player) {  //// Из пакета в игрока
    float x, y;
    bool turnedRight;
    packet >> x >> y >> turnedRight;
    player.setTurnedRight(turnedRight);
    player.setX(x);
    player.setY(y);

    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const bool* directions) {  //// Из массива направлений в пакет
    return packet << directions[0] << directions[1] << directions[2] << directions[3];
}

sf::Packet& operator >> (sf::Packet& packet, bool* directions) {  //// Из пакета в массив направлений
    return packet >> directions[0] >> directions[1] >> directions[2] >> directions[3];
}

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