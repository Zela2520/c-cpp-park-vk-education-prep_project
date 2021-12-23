#ifndef APPLICATION_INCLUDE_MAP_H
#define APPLICATION_INCLUDE_MAP_H

#include "model.h"
#include "wall.h"

#define HEIGHT_MAP (40)

class Map {
private:
    int width = 0;    //// ширина карты в блоках
    int height = 0;     //// высота карты в блоках
    std::vector<Wall> walls;
public:
    explicit Map(char* fileName, const sf::Texture& globalBoundTexture, const sf::Texture& localBoundTexture);   //// Создаём карту из файла.
    void draw(sf::RenderWindow &window) const; //// рисуем карту
    std::vector<Wall>& getWalls();
};




#endif // APPLICATION_INCLUDE_MAP_H
