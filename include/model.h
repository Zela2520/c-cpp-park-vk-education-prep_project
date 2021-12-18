#ifndef PROJECT_INCLUDE_MODEL_H_
#define PROJECT_INCLUDE_MODEL_H_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <map>



class Object {

protected:
    float m_x; // начальные координаты объекта
    float m_y; // начальные координаты объекта
    float m_default_width;
    float m_default_height;
    float m_x_scale; // начальный масштаб x
    float m_y_scale; // начальный масштаб y
    float m_rotation; // угол поворота
    sf::Sprite m_sprite; // поля для отображения объекта в игре
    bool m_turned_right; // поворот направо

public:
    // подписать, что деалает каждая функция и где она испоьзуется
    Object();
    sf::Sprite getSprite() const; // берём спрайт текущего объекта
    float getX() const; // берём координату
    float getY() const; // берём координату
    float getWidth() const; // берём ширину
    float getHeight() const; // берём высоту
    float getRotation() const; //  берём угол поворота
    float getXScale() const; // берём масштаб
    float getYScale() const; // берём масштаб
    void setScale(float x, float y); // устанавливаем масштаб
    void setX(float x); // устанавливаем координаты
    void setY(float y); // устанавливаем координаты
    void setRotation(float rotation); // устанавливаем угол поворота
    void setTurnedRight(bool turnedRight); // устанавливаем ориентацию героя
    void goUp(float distance = 1); // поднимаемся вверх
    void goDown(float distance = 1); // опускаемся вниз
    void goRight(float distance = 1); // идём вправо
    void goLeft(float distance = 1); // идём влево
    virtual void draw(sf::RenderWindow& window); // почему так ? Зачем оно надо ?
};

class Unmovable : public Object {
public:
    Unmovable(float x, float y, const sf::Texture &texture); // конструктор неподвижных объектов
    friend sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable);
    friend sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable);
};

class Player : public Object {
public:
    static size_t count;
    Player(float x, float y, const sf::Texture& texture); // конструктор игрока
    bool intersects_with(std::vector<Unmovable>& objects); // отслеживаем пересечение игррока с объектами
    void draw(sf::RenderWindow& window) override; // рисуем окно
    size_t get_id();
    friend sf::Packet& operator >> (sf::Packet& packet, Player& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Player& player);
private:
    size_t m_id;
};

size_t Player::count = 0;

class Enemy : public Object {
    Enemy(float x, float y, const sf::Texture& texture); // конструктор игрока
    bool intersects_with_hero(std::vector<Player>& players); // отслеживаем пересечение игррока с объектами
    bool intersects_with(std::vector<Unmovable>& objects);
    void draw(sf::RenderWindow& window) override; // рисуем окно
    friend sf::Packet& operator >> (sf::Packet& packet, Enemy& player);
    friend sf::Packet& operator << (sf::Packet& packet, const Enemy& player);
};

sf::Packet& operator >> (sf::Packet& packet, bool* directions);
sf::Packet& operator << (sf::Packet& packet, const bool* directions);




#endif // PROJECT_INCLUDE_MODEL_H_