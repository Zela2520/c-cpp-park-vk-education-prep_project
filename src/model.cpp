#include "model.h"

using namespace sf;
using namespace std;

Sprite& Object::getSprite() {
    return sprite;
}
float Object::getX() const {
    return sprite.getPosition().x;
}
float Object::getY() const {
    return sprite.getPosition().y;
}
void Object::setX(float _x) {
    sprite.setPosition(_x, this->getY());
}
void Object::setY(float _y) {
    sprite.setPosition(this->getX(), _y);
}
void Object::goUp(float distance) {
    sprite.setPosition(this->getX(), this->getY() - distance);
}
void Object::goDown(float distance) {
    sprite.setPosition(this->getX(), this->getY() + distance);
}
void Object::goRight(float distance) {
    sprite.setPosition(this->getX() + distance, this->getY());
}
void Object::goLeft(float distance) {
    sprite.setPosition(this->getX() - distance, this->getY());
}
void Object::draw(RenderWindow& window) {
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
Unmovable::Unmovable(float _x, float _y) {
    this->setX(_x);
    this->setY(_y);
}

Player::Player(float _x, float _y, const Texture& texture) : Object() {
    sprite.setTexture(texture);
    sprite.scale(1, 1);  // Масштабировани модели
    this->setX(_x);
    this->setY(_y);
}
Player::Player(float _x, float _y) : Object() {
    sprite.scale(1, 1);  // Масштабировани модели
    this->setX(_x);
    this->setY(_y);
}
bool Player::intersectsWith(vector<Unmovable>& objects) {
    for (auto& object : objects) {
        Rect<float> thisBounds = sprite.getGlobalBounds();
        Rect<float> objectBounds = object.getSprite().getGlobalBounds();

        border.setPointCount(4);
        border.setPosition(thisBounds.left, thisBounds.top);
        border.setRadius(thisBounds.width);
        border.setOutlineColor(Color::Green);
        border.setOutlineThickness(10);

        Rect<float> scaledThisBounds(thisBounds.left, thisBounds.top, thisBounds.width*sprite.getScale().x, thisBounds.height*sprite.getScale().y);
        Rect<float> scaledObjectBounds(objectBounds.left, objectBounds.top, objectBounds.width*object.getSprite().getScale().x, objectBounds.height*object.getSprite().getScale().y);
        if (scaledThisBounds.intersects((scaledObjectBounds))) {
            std::cout << "ПЕРЕСЕЧЕНИЕ" << endl;
            cout << scaledThisBounds.left << " " << scaledThisBounds.top << " " << scaledThisBounds.height << " " << scaledThisBounds.width << endl;
            cout << scaledObjectBounds.left << " " << scaledObjectBounds.top << " " << scaledObjectBounds.height << " " << scaledObjectBounds.width << endl;
            return true;
        } else {
            cout << "НЕТ ПЕРЕСЕЧЕНИЯ" << endl;
            cout << scaledThisBounds.left << " " << scaledThisBounds.top << " " << scaledThisBounds.height << " " << scaledThisBounds.width << endl;
            cout << scaledObjectBounds.left << " " << scaledObjectBounds.top << " " << scaledObjectBounds.height << " " << scaledObjectBounds.width << endl;
        }
    }

    return false;
}



sf::Packet& operator << (sf::Packet& packet, const Player& player) {  // Из игрока в пакет
    return packet << player.getX() << player.getY();
}
sf::Packet& operator >> (sf::Packet& packet, Player& player) {  // Из пакета в игрока
    float x, y;
    packet >> x >> y;
    player.setX(x);
    player.setY(y);
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