#include "../../include/mob.h"

Mob::Mob(float _x, float _y, const sf::Texture& texture) {
    sprite.setTexture(texture);
    setX(_x);
    setY(_y);
    setScale(1.5, 1.5);
}


sf::Vector2<float> Mob::getPlayersCoords(const Player& player) {
    sf::Vector2<float> playersCoords(player.getX(), player.getY());
    return playersCoords;
}

sf::Vector2<float> Mob::moveMob(Player& player, std::vector<Wall>& walls, float time) {   //// будем передавать вектор игроков и добавим циклы.
    sf::Vector2<float> playersCoords = getPlayersCoords(player);
    sf::Vector2<float> mobCoords(getX(), getY());
    sf::Vector2<float> movingDir(playersCoords.x - mobCoords.x, playersCoords.y - mobCoords.y);


    float hyppotenuse = sqrt(pow(playersCoords.x - mobCoords.x, 2) + pow(playersCoords.y - mobCoords.y, 2));
    hyppotenuse *= 1.8;
    if (hyppotenuse != 0) {
        movingDir.x /= hyppotenuse;
        movingDir.y /= hyppotenuse;
    }



    this->setX(movingDir.x + this->getX());
    if (this->intersectsWith(walls)) {
        this->setX(this->getX() - movingDir.x);
    }
    this->setY(movingDir.y + this->getY());
    if (this->intersectsWith(walls)) {
        this->setY(this->getY() - movingDir.y);
    }
    return movingDir;
}

bool Mob::intersectsWith(std::vector<Wall>& objects) {
    for (auto& object : objects) {
        sf::Rect<float> thisBounds = sprite.getGlobalBounds();
        sf::Rect<float> objectBounds = object.getSprite().getGlobalBounds();

        if (thisBounds.intersects(objectBounds)) return true;
    }
    return false;
}

//void Mob::moveMobeX(std::vector<Wall> &walls) {
//}
//
//void Mob::moveMobeY(std::vector<Wall> &walls) {
//
//}

Player& Mob::setTaregt(std::vector<Player>& players) {
    float xMob = this->getX();
    float yMob = this->getY();
    float minPath = 10000;
//    Player target;
    int indexPlayer = 0;
    for (int i = 0; i < players.size(); ++i) {
        float xPlayer = players[i].getX();
        float yPlayer = players[i].getY();
        float currentPath = static_cast<float>(pow(pow(xPlayer - xMob, 2) + pow(yPlayer - yMob, 2), 0.5));
        if (currentPath < minPath) {
            minPath = currentPath;
//            target = players[i];
            indexPlayer = i;
        }
    }
    return players[indexPlayer];
}



sf::Packet& operator << (sf::Packet& packet, const Mob& mob) {  //// Из игрока в пакет
    return packet << mob.getX() << mob.getY();
}

sf::Packet& operator >> (sf::Packet& packet, Mob& mob) {  //// Из пакета в игрока
    float x, y;
    packet >> x >> y;
    mob.setX(x);
    mob.setY(y);

    return packet;
}