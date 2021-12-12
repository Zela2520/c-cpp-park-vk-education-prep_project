#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>

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

    // инициализируем начальное положение объектов на карте, принимая данные от сервера
    std::vector<Ball> user_balls(2);
    for (auto &ball : user_balls) {
        socket.receive(packet);
        packet >> ball;
        packet.clear();

        // каждый клиент печатает информацию о пришедших к нему мячиках
        std::cout << ball.x << ' ' << ball.y << ' ' << ball.color << '\n';
    }

    // отрисуем окно c белым цветом
    sf::RenderWindow window(sf::VideoMode(320, 420), "Squid game");
    window.clear(sf::Color::White);

    // отрисуем мячик с начальными координатами
    sf::CircleShape circle;
    for (auto &ball : user_balls) {
        circle.setPosition(ball.x, ball.y);
        circle.setRadius(15.f);
        circle.setFillColor(sf::Color::Black);
        window.draw(circle);
    }
    window.display();


    // выполняем действия над объектом конкретного клиента
    while (window.isOpen()) {
        sf::Event event; // переменная для отслеживания событий, происходящих на кажой итерации цикла
        std::string dir;  // направление движения, которое будет обрабатваться на сервере

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (window.hasFocus()) {
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
        }

        // запаковываем данные пользователя в пакет и отправляем на сервер
        packet << dir;
        socket.send(packet);
        packet.clear();
        // std::cout << dir << '\n';

        // Отрисовываем все мячи у каждого пользователя
        // получаем обработанные(обновлённые) данные с сервера
        window.clear(sf::Color::White);
        for (int i = 0; i < user_balls.size(); ++i) {
            socket.receive(packet);
            packet >> user_balls[i];
            packet.clear();
            std::cout << user_balls[i].x << ' '<< user_balls[i].y << ' ' << user_balls[i].color << '\n';
            circle.setPosition(user_balls[i].x, user_balls[i].y);
            window.draw(circle);
        }
        window.display();
    }
    return 0;
}