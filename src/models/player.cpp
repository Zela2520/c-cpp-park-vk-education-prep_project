#include "../../include/player.h"

Player::Player(float _x, float _y, const sf::Texture& _texture) : Object() {  //// Конструктор инициализации игрока.
    sprite.setTexture(_texture);
    defaultWidth = sprite.getGlobalBounds().width;
    defaultHeight = sprite.getGlobalBounds().height;
    setScale(0.1, 0.1);  //// Масштабировани модели
    setX(_x);
    setY(_y);
}

bool Player::intersectsWith(std::vector<Unmovable>& objects) {
    for (auto& object : objects) {
        sf::Rect<float> thisBounds = sprite.getGlobalBounds();
        sf::Rect<float> objectBounds = object.getSprite().getGlobalBounds();

        return (thisBounds.intersects(objectBounds));
    }
    return false;
}

void Player::draw(sf::RenderWindow& window) {
    if (turnedRight) {
        sprite.setTextureRect(sf::IntRect(0, 0, (int)defaultWidth, (int)defaultHeight));
    }
    if (!turnedRight) {
        sprite.setTextureRect(sf::IntRect(0 + (int)defaultWidth, 0, - (int)defaultWidth,(int)defaultHeight));
    }
    window.draw(sprite);
}

void Player::setId(int _gotId) {
    Id = _gotId;
}

int Player::getId() const {
    return Id;
}

sf::Packet& operator << (sf::Packet& packet, const Player& player) {  //// Из игрока в пакет
    return packet << player.getId() << player.getX() << player.getY() << player.turnedRight;
}
sf::Packet& operator >> (sf::Packet& packet, Player& player) {  //// Из пакета в игрока
    float x, y;
    int id;
    bool turnedRight;
    packet >> id >> x >> y >> turnedRight;
    player.setTurnedRight(turnedRight);
    player.setX(x);
    player.setY(y);
    player.setId(id);

    return packet;
}

