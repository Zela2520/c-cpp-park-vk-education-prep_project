#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

struct Ball {
    int x;
    int y;
    std::string color;
};

sf::Packet& operator <<(sf::Packet& packet, const Ball& ball)
{
    return packet << ball.x << ball.y << ball.color;
}

sf::Packet& operator >>(sf::Packet& packet, Ball& ball)
{
    return packet >> ball.x >> ball.y >> ball.color;
}

int main() {
    setlocale(LC_ALL, "");
    sf::TcpSocket socket;
    socket.connect("127.0.0.1", 3000); // подключаемся к серверу по заданному порту
    sf::Packet packet; // создаём пакет для общения клиента с сервером

    // инициализируем начальное положение объекта, принимая данные от сервера
    socket.receive(packet);
    Ball user_ball;
    packet >> user_ball;
    packet.clear();

    // отрисуем окно c белым цветом
    sf::RenderWindow window(sf::VideoMode(320, 420), "Squid game");
    window.clear(sf::Color::White);

    //  отрисуем мячик с начальными координатами
    sf::CircleShape circle;
    circle.setPosition(user_ball.x, user_ball.y);
    circle.setRadius(15.f);
    circle.setFillColor(sf::Color::Black);
    window.draw(circle);
    window.display();

    // выполняем действия над объектом
    while (window.isOpen()) {
        sf::Event event; // переменная для отслеживания событий, происходящих на кажой итерации цикла
        std::string dir;  // направление движения, которое будет обрабатваться на сервере
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

            // запаковываем данные пользователя в пакет и отправляем на сервер
            packet << dir;
            socket.send(packet);
            packet.clear();

            // получаем обработанные(обновлённые) данные с сервера
            socket.receive(packet);
            packet >> user_ball;
            circle.setPosition(user_ball.x, user_ball.y);
            window.clear(sf::Color::White);
            window.draw(circle);
            window.display();
        }
    }






    return 0;
}