#include "connection.h"
struct Ball {
    int x;
    int y;
    std::string color;
};

int main() {
    setlocale(LC_ALL, "");
    sf::TcpSocket socket;
    socket.connect("127.0.0.1", 3000);
    sf::Packet packet;
    socket.receive(packet);


    sf::RenderWindow window(sf::VideoMode(320, 480), "The Game!");


    while (window.isOpen())
    {
        sf::Event event;

        int x, y;
        std::string color;
        sf::CircleShape circle;
        while (packet >> x >> y >> color) {
            circle.setPosition(x, y);
            circle.setFillColor(sf::Color::Black);
            circle.setRadius(10.f);
            window.draw(circle);
        }
        window.clear(sf::Color::White);
        window.display();

        std::string dir;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                dir = "UP";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                dir = "DOWN";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                dir = "RIGHT";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                dir = "LEFT";
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            packet.clear();
            packet << dir; //Пакуем значения координат в Пакет
            socket.send(packet);    //Отправка данных
            packet.clear();            //Чистим пакет
            sleep(sf::milliseconds(10)); //Задержка
        }
    }
    return 0;
}