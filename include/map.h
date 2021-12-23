#ifndef APPLICATION_INCLUDE_MAP_H
#define APPLICATION_INCLUDE_MAP_H

#include "model.h"
#include "unmovable.h"

#define HEIGHT_MAP (40)

class Map {
private:
    int width;    //// ширина карты в блоках
    int height;     //// высота карты в блоках
    sf::Texture wallTexture;    //// текстура блока стены
    sf::Sprite wallSprite;    //// спарйт блока стены
    std::vector<Wall> walls;
public:
    explicit Map(const char* fileName);   //// Создаём карту из файла.
    void draw(sf::RenderWindow &window) const; //// рисуем карту
    std::vector<Wall>& getWalls();
};




#endif // APPLICATION_INCLUDE_MAP_H
