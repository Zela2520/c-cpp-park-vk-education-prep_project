#include "../../include/map.h"

#include <iostream>

#define HEIGHT_MAP (40)
#define WIDTH_MAP (40)

//// добавить сюда Unmoveables для взаимодействия героя с картой
//// когда встречаю 's' пушу в вектор unmovables очередной объект



Map::Map() {
    map_width = WIDTH_MAP;
    map_height = HEIGHT_MAP;
}

void Map::creat_map(std::vector<Unmovable> &static_objects, sf::Texture *unmovable_object) {
    for (size_t i = 0; i < map_height; ++i) {
        for (size_t j = 0; j < map_width; ++j) {
            sf::RectangleShape tempRectangle; //// создаём временную переменную для того, чтобы пушить её в вектор
            tempRectangle.setSize(sf::Vector2f(100, 100)); //// задаём размер неподвижным объектам
            if (map[i][j] == '0') {
                tempRectangle.setTexture(unmovable_object);
                static_objects.emplace_back(tempRectangle);
                std::cout << "Black\n";
            }
            if (map[i][j] == 's') {
                tempRectangle.setTexture(unmovable_object);
                static_objects.emplace_back(tempRectangle);
                std::cout << "Green\n";
            }
            if (map[i][j] == ' ') {
                tempRectangle.setFillColor(sf::Color::Yellow);
                std::cout << "Yellow\n";
            }

            tempRectangle.setPosition(j * 32, i * 32); //// устанавливаем позицию на карте каждому прямоугольнику
            m_rectangles.emplace_back(tempRectangle);
        }
    }
    std::cout << "LOL\n";
}

void Map::draw_map(sf::RenderWindow &window) {
    for(size_t i = 0; i < m_rectangles.size(); ++i) {
        window.draw(m_rectangles[i]);
    }
}