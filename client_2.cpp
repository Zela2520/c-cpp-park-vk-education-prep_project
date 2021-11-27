#include "connection.h"

int main() {
    setlocale(LC_ALL, "");
    sf::TcpSocket socket;
    socket.connect("127.0.0.1", 3000);
    sf::Packet packet;
    sf::CircleShape circle;
    circle.setFillColor(sf::Color::Green);
    socket.receive(packet);
    sf::Vector2f coords;
    coords.x = 100.f;
    coords.y = 100.f;
    circle.setRadius(100);
    circle.setPosition(coords);
    sf::RenderWindow window(sf::VideoMode(320, 480), "The Game!");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                coords.y -= 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                coords.y += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                coords.x += 10;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                coords.x -= 10;
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            packet << coords.x << coords.y;        //Пакуем значения координат в Пакет
            socket.send(packet);    //Отправка данных
            packet.clear();            //Чистим пакет
            socket.receive(packet);
//            sleep(sf::milliseconds(10));//Задержка
//            socket.receive()
        }
        window.clear();
        window.draw(circle);
        window.display();
    }
    return 0;
}