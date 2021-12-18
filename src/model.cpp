#include "../include/model.h"

#define DEFAULT_COORD_X (0)
#define DEFAULT_COORD_Y (0)
#define DEFAULT_SIZE_X (-1)
#define DEFAULT_SIZE_Y (-1)
#define DEFAULT_SCALE_X (1)
#define DEFAULT_SCALE_Y (1)
#define DEFAULT_ENGLE (0)

Object::Object() {
    m_x = DEFAULT_COORD_X;
    m_y = DEFAULT_COORD_Y;
    m_default_width = DEFAULT_SIZE_X;
    m_default_height = DEFAULT_SIZE_Y;
    m_x_scale = DEFAULT_SCALE_X;
    m_y_scale = DEFAULT_SCALE_Y;
    m_rotation = DEFAULT_ENGLE;
    m_turned_right = true;
}

sf::Sprite Object::getSprite() const {
    return m_sprite;
}

float Object::getX() const {
    return m_x;
}

float Object::getY() const {
    return m_y;
}

float Object::getWidth() const {
    return m_default_width;
}

float Object::getHeight() const {
    return m_default_height;
}

float Object::getRotation() const {
    return m_rotation;
}
float Object::getXScale() const {
    return m_x_scale;
}
float Object::getYScale() const {
    return m_y_scale;
}

void Object::setX(float x) {
    m_x = x;
    m_sprite.setPosition(m_x, m_y);
}

void Object::setY(float y) {
    m_y = y;
    m_sprite.setPosition(m_x, m_y);
}

void Object::setRotation(float rotation) {
    m_rotation = rotation;
    m_sprite.setRotation(rotation);
}

void Object::setTurnedRight(bool turned_right) {
    m_turned_right = turned_right;
}

void Object::setScale(float xScale, float yScale) {
    m_x_scale = xScale;
    m_y_scale = yScale;
    m_sprite.setScale(xScale, yScale);
}

void Object::goUp(float distance) {
    m_y -= distance;
    m_sprite.move(0, -distance);
}

void Object::goDown(float distance) {
    m_y += distance;
    m_sprite.move(0, distance);
}

void Object::goRight(float distance) {
    m_x += distance;
    m_sprite.move(distance, 0);
    m_turned_right = true;
}

void Object::goLeft(float distance) {
    m_x -= distance;
    m_sprite.move(-distance, 0);
    m_turned_right = false;
}

void Object::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

Unmovable::Unmovable(float x, float y, const sf::Texture& texture) : Object() {
    m_sprite.setTexture(texture);
    setX(x);
    setY(y);
}


Player::Player(float x, float y, const sf::Texture& texture) : Object() {  //// Конструктор инициализации игрока.
    m_sprite.setTexture(texture);
    m_default_width = m_sprite.getGlobalBounds().width;
    m_default_height = m_sprite.getGlobalBounds().height;
    ++count;
    m_id = count;
    setScale(0.1, 0.1);  //// Масштабировани модели
    setX(x);
    setY(y);
}

size_t Player::get_id() {
    return m_id;
}

bool Player::intersects_with(std::vector<Unmovable>& objects) {
    // перебираем все объекты на карте и смотрим какие объекты пересекаются с игроком
    for (auto& object : objects) {
        sf::Rect<float> this_bounds = m_sprite.getGlobalBounds(); // сохраняем глобальные координаты игрока
        sf::Rect<float> object_bounds = object.getSprite().getGlobalBounds(); // сохраняем глобальные координаты объекта
        return (this_bounds.intersects(object_bounds)); // сравниваем глобальные координаты игрока и глобальные координаты объекта
    }
    return false; // если пересечения границ отсутствует возвращаем false
}

void Player::draw(sf::RenderWindow& window) { // рисуем окно в завсимости от ориентация персонажа
    std::cout << "Дефолтные размеры " << m_default_width << "x" << m_default_height << std::endl;
    if (m_turned_right) {
        m_sprite.setTextureRect(sf::IntRect(0, 0, (int)m_default_width, (int)m_default_height));
    }
    if (!m_turned_right) {
        m_sprite.setTextureRect(sf::IntRect(0 + (int)m_default_width, 0, -(int)m_default_width,(int)m_default_height));
    }
    window.draw(m_sprite);
}



sf::Packet& operator << (sf::Packet& packet, const Player& player) {  //// Из игрока в пакет
    return packet << player.getX() << player.getY() << player.m_turned_right;
}

sf::Packet& operator >> (sf::Packet& packet, Player& player) {  //// Из пакета в игрока
    float x, y;
    bool turnedRight;
    packet >> x >> y >> turnedRight;
    player.setTurnedRight(turnedRight);
    player.setX(x);
    player.setY(y);

    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const bool* directions) {  //// Из массива направлений в пакет
    return packet << directions[0] << directions[1] << directions[2] << directions[3];
}

sf::Packet& operator >> (sf::Packet& packet, bool* directions) {  //// Из пакета в массив направлений
    return packet >> directions[0] >> directions[1] >> directions[2] >> directions[3];
}

sf::Packet& operator >> (sf::Packet& packet, Unmovable& unmovable) {  //// Пакета в статичный объект
    float x, y;
    packet >> x >> y;
    unmovable.setX(x);
    unmovable.setY(y);
    return packet;
}

sf::Packet& operator << (sf::Packet& packet, const Unmovable& unmovable) {  //// Из статичного объекта в пакет
    return packet << unmovable.getX() << unmovable.getY();
}