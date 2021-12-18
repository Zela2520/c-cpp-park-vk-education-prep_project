#include "../include/map.h"

Map::Map() {
    map_image.loadFromFile("../include/map.png");
    map_texture.loadFromImage(map_image);
    map_sprite.setTexture(map_texture);
};

Map::Map(std::string path_to_file) {
    map_image.loadFromFile(path_to_file);
    map_texture.loadFromImage(map_image);
    map_sprite.setTexture(map_texture);
}

void Map::draw_map() {
    for (int i = 0; i < HEIGHT_MAP; i++)
        for (int j = 0; j < WIDTH_MAP; j++) {
            if (m_tile_map[i][j] == ' ')  {
                map_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); //// если встретили символ пробел, то рисуем 1й квадратик
            }
            if (m_tile_map[i][j] == 's')  {
                map_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
            }
            if ((m_tile_map[i][j] == '0')) {
                map_sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
            }

            map_sprite.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

           // sf::window.draw(map_sprite);//рисуем квадратики на экран
        }
}
