#ifndef APPLICATION_MAP_H
#define APPLICATION_MAP_H

#include "model.h"

#define HEIGHT_MAP (400)
#define WIDTH_MAP (500)

class Map {
private:
    sf::String m_tile_map[HEIGHT_MAP] = {
            "00000000000000000000000000000000000000000000000000000000000000000",
            "0                                                               0",
            "0                                                               0",
            "0          ssssssssssss                                         0",
            "0                                                               0",
            "0                                     ssssssssssssss            0",
            "0                                                               0",
            "0                      sss                                      0",
            "0                                             ssss              0",
            "0            sssss                                              0",
            "0                                                               0",
            "0                                      sssss                    0",
            "0             s                                                 0",
            "0                                                               0",
            "0        s                                                      0",
            "0                                                               0",
            "0                      sssss                                    0",
            "0                                                               0",
            "0       sssssss                                                 0",
            "0                                                               0",
            "0                                                               0",
            "0                                            ssssssssss         0",
            "0                                                               0",
            "0        sssss                                                  0",
            "0                       sssssss                                 0",
            "0                                                               0",
            "0                                                               0",
            "0                                        sssss                  0",
            "0          ssss                                                 0",
            "0                                                       sssssss 0",
            "0                                                               0",
            "0              sssssss                                          0",
            "0                                                               0",
            "0                                                               0",
            "00000000000000000000000000000000000000000000000000000000000000000"
    }; //// визуал карты
    size_t map_width = WIDTH_MAP; //// ширина карты
    size_t map_height = HEIGHT_MAP; //// высота карты
    sf::Image map_image; //// картинка откуда будет загружаться карта
    sf::Texture map_texture; //// текстура из картинки
    sf::Sprite map_sprite; //// спарйт для карты

public:
    Map();
    Map(std::string path_to_file);
    ~Map() = default;
    void draw_map();
};

#endif //APPLICATION_MAP_H
