#include "../../include/map.h"
#include <iostream>

#define HEIGHT_MAP (40)
#define WIDTH_MAP (40)
#define ZERO (0)

Map::Map() {
    map_width = WIDTH_MAP;
    map_height = HEIGHT_MAP;
    // m_rectangles.reserve(map_width * map_height);
    // map_texture.loadFromFile("../../include/map_2.jpg");
    // map_sprite.setTexture(map_texture);
}

void Map::draw_map(sf::RenderWindow &window) {
    for (size_t i = 0; i < map_height; ++i) {
        for (size_t j = 0; j < map_width; ++j) {
            sf::RectangleShape tempRectangle; //// создаём временную переменную для того, чтобы пушить её в вектор
            tempRectangle.setSize(sf::Vector2f(100, 100));
            if (map[i][j] == '0') {
                tempRectangle.setFillColor(sf::Color::Black);
                std::cout << "Black\n";
            }
            if (map[i][j] == 's') {
                tempRectangle.setFillColor(sf::Color::Green);
                std::cout << "Green\n";
            }
            if (map[i][j] == ' ') {
                tempRectangle.setFillColor(sf::Color::Red);
                std::cout << "Red\n";
            }

            tempRectangle.setPosition(j * 32, i * 32); //// устанавливаем позицию на карте каждому прямоугольнику
            m_rectangles.emplace_back(tempRectangle);
            window.draw(tempRectangle);
        }
    }
    std::cout << "LOL\n";
}
