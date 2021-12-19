#include "../../include/player.h"
#include "../../include/mob.h"

Mob::Mob(float _x, float _y, const sf::Texture& texture) {
    sprite.setTexture(texture);
    setX(_x);
    setY(_y);
}


sf::Vector2<float> Mob::getPlayersCoords(const Player player) {
    sf::Vector2<float> playersCoords(player.getX(), player.getY());
    return playersCoords;
}

sf::Vector2<float> Mob::moveMob(Player player) {
    sf::Vector2<float> playersCoords = getPlayersCoords(player);
    sf::Vector2<float> mobCoords(this->getX(), this->getY());
    sf::Vector2<float> movingDir(playersCoords.x - mobCoords.x, playersCoords.y - mobCoords.y);
    movingDir.x /= static_cast<float>(pow(pow(playersCoords.x - mobCoords.x, 2) + pow(playersCoords.y - mobCoords.y, 2), 0.5));
    movingDir.y /= static_cast<float>(pow(pow(playersCoords.x - mobCoords.x, 2) + pow(playersCoords.y - mobCoords.y, 2), 0.5));
    this->setX(movingDir.x + this->getX());
    this->setY(movingDir.y + this->getY());
    return movingDir;
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
