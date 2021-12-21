#ifndef APPLICATION_INCLUDE_MAP_H
#define APPLICATION_INCLUDE_MAP_H

#include "model.h"
#include "unmovable.h"

#define HEIGHT_MAP (40)

class Map {

private:
    size_t map_width; //// ширина карты
    size_t map_height; //// высота карты
    std::vector<sf::RectangleShape> m_rectangles; //// массив прямоугольников которыми будет заполнена карта
    sf::Texture map_texture; //// текстура из картинки
    sf::Sprite map_sprite; //// спарйт для карты
    sf::String map[HEIGHT_MAP] = {
            "0000000000000000000000000000000000000000",
            "0                                      0",
            "0                                      0",
            "0          ssssssssssss                0",
            "0                                      0",
            "0     ssssssssssssss                   0",
            "0                                      0",
            "0                      sss             0",
            "0                   ssss               0",
            "0            sssss                     0",
            "0                                      0",
            "0                                      0",
            "0                        sss           0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0       sss                            0",
            "0                                      0",
            "0                                      0",
            "0                    sss               0",
            "0                                      0",
            "0                                      0",
            "0             sss                      0",
            "0                             sss      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0         sss                          0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                        sss           0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0                                      0",
            "0000000000000000000000000000000000000000",
    }; //// визуал карты

public:
    Map(); //// загружаем текстуру, устанавливаем спрайт, задаём размеры
    ~Map() = default;
    void creat_map(std::vector<Unmovable> &static_objects, sf::Texture *unmovable_object); //// заполняем массив прямоугольников нужными прямоугольниками
    void draw_map(sf::RenderWindow &window); //// рисуем карту
};




#endif // APPLICATION_INCLUDE_MAP_H
