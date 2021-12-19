#include "../../include/map.h"


globalBound::globalBound(float _x, float _y, const sf::Texture& texture) : Object() {
    sprite.setTextureRect(sf::IntRect(40, 40, 219, 219));  //// Tut nado vibrat' coordinati
    setX(_x);
    setY(_y);
}

localBound::localBound(float _x, float _y, const sf::Texture& texture) : Object() {
    sprite.setTextureRect(sf::IntRect(40, 40, 219, 219));
    setX(_x);
    setY(_y);
}

void Map::getBounds(std::vector<localBound>& localBounds, std::vector<globalBound> globalBounds, const sf::Texture& localBoundsTexture, const sf::Texture& globalBoundsTexture) const {
    char c = 0;
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            if (map[i][j] == '0') {
                globalBounds.emplace_back(globalBound(j * 219, i * 219, globalBoundsTexture));
            }
            if (map[i][j] == 's') {
                localBounds.emplace_back(localBound(j * 219, i * 219, localBoundsTexture));
            }
            if (map[i][j] == ' ') {
                continue;
            }
        }
    }
}