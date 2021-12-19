#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <cmath>
#include "../include/model.h"
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
void Object::move(float x, float y) {
    setX(getX() + x);
    setY(getY() + y);
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
    window.draw(sprite);
}

Unmovable::Unmovable(float _x, float _y, const Texture& texture) : Object() {
    sprite.setTexture(texture);
    defaultWidth = sprite.getGlobalBounds().width;
    defaultHeight = sprite.getGlobalBounds().height;
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
}

void Player::draw(RenderWindow& window) {
    cout << "Дефолтные размеры " << defaultWidth << "x" << defaultHeight << endl;
    if (turnedRight) {
        sprite.setTextureRect(IntRect(0, 0, (int)defaultWidth, (int)defaultHeight));
//        cout << "ПРАВАК " << sprite.getGlobalBounds().width << endl;
//        cout << "ПРАВАК " << sprite.getGlobalBounds().height << endl;
    }
     if (!turnedRight) {
//         cout << "Левак!" << sprite.getGlobalBounds().width << endl;
//        cout << "Левак!" << sprite.getGlobalBounds().height << endl;
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


Turret::Turret(float _x, float _y, const Texture& texture) {
    sprite.setTexture(texture);
    defaultWidth = sprite.getGlobalBounds().width;
    defaultHeight = sprite.getGlobalBounds().height;
    setX(_x);
    setY(_y);
}

Bullet::Bullet(float _x, float _y, float _rotation, const Texture& texture) {
    sprite.setTexture(texture);
    setX(_x);
    setY(_y);
    setRotation(_rotation);
    defaultWidth = sprite.getGlobalBounds().width;
    defaultHeight = sprite.getGlobalBounds().height;
    isAlive = true;
}

double sqr(double n) {
    return n*n;
}

double getDistance(const Turret& turret, Player& player) {
    return sqrt(sqr(player.getX() + player.getWidth()/2 - turret.getX() - turret.getWidth()) + sqr(player.getY() + player.getHeight()/2 - turret.getY() - turret.getHeight()));
}

Player& Turret::getClosestPlayer(vector<Player>& players) const {
    double minDistance = sqrt(sqr(players[0].getX() + players[0].getWidth()/2 - getX() - getWidth()) + sqr(players[0].getY() + players[0].getHeight()/2 - getY() - getHeight()));
    Player *closestPlayer;
    for (auto& player : players) {
        if (getDistance(*this, player) < minDistance) {
            minDistance = getDistance(*this, player);
            closestPlayer = &player;
        }
    }
    return *closestPlayer;
}

float Turret::getDirection(Player& player) const {
    float tg = (player.getY() - getY()) / (player.getX() - getX());
    return atan(tg);
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

sf::Packet& operator >> (sf::Packet& packet, Turret& turret) {
    float x, y;
    packet >> x >> y;
    turret.setX(x);
    turret.setY(y);
    return packet;
}
sf::Packet& operator << (sf::Packet& packet, const Turret& turret) {
    return packet << turret.getX() << turret.getY();
}

sf::Packet& operator >> (sf::Packet& packet, Bullet& bullet) {
    float x, y, rotation;
    packet >> x >> y >> rotation;
    bullet.setX(x);
    bullet.setY(y);
    bullet.setRotation(rotation);
    return packet;
}
sf::Packet& operator << (sf::Packet& packet, const Bullet& bullet) {
    return packet << bullet.getX() << bullet.getY() << bullet.getRotation();
}