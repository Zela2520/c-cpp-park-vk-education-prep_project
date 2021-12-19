#ifndef APPLICATION_MAP_H
#define APPLICATION_MAP_H

#include "model.h"

#define HEIGHT_MAP (400)
#define WIDTH_MAP (500)

class globalBound : public Object {
public:
    globalBound(float _x, float _y, const sf::Texture& texture);
};
class localBound : public Object {
public:
    localBound(float _x, float _y, const sf::Texture& texture);
};

class Map {
private:
    sf::String map[HEIGHT_MAP] = {
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
    Map() = default;
//    Map(std::string path_to_file);
    ~Map() = default;
    void draw_map();
    void getBounds(std::vector<localBound>& localBounds, std::vector<globalBound> globalBounds, const sf::Texture&, const sf::Texture&) const;
};




#endif //APPLICATION_MAP_H
