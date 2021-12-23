#include "../../include/map.h"

#include <iostream>

#define HEIGHT_MAP (40)
#define WIDTH_MAP (40)

//// добавить сюда Unmoveables для взаимодействия героя с картой
//// когда встречаю 's' пушу в вектор unmovables очередной объект



Map::Map(const char* fileName) {
    FILE* source = fopen(fileName, "r+");
    if (source == nullptr) {
        printf("Couldn't open file\n");
        exit(1);
    }

    char c = fgetc(source);    //// Получаем символ из файла
    for (int i = 0; c != EOF; ++i) {
        c = 0;
        for (int j = 0; c != EOF && c != '\n'; ++j) {
            c = fgetc(source);
//            sf::RectangleShape tempRectangle; //// создаём временную переменную для того, чтобы пушить её в вектор
//            tempRectangle.setSize(sf::Vector2f(100, 100)); //// задаём размер неподвижным объектам
            if (c == '0') {
                walls.emplace_back(Wall(j * 100, i * 100, wallTexture));
            }
            if (c == 's') {
                walls.emplace_back(Wall(j * 100, i * 100, wallTexture));
            }
        }
    }
    std::cout << "LOL\n";
}

std::vector<Wall>& Map::getWalls() {
    return walls;
}

void Map::draw(sf::RenderWindow &window) const {
    for (auto& wall : walls) {
        wall.draw(window);
    }
}