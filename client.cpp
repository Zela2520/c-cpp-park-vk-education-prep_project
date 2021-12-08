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

sf::Packet& operator << (sf::Packet& packet, const Ball& ball)
{
    return packet << ball.x << ball.y << ball.color;
}

sf::Packet& operator >> (sf::Packet& packet, Ball& ball)
{
    return packet >> ball.x >> ball.y >> ball.color;
}



int main() {
    setlocale(LC_ALL, "");
    
    sf::TcpSocket socket;  // Создаем сокет. У каждого клиента - свой сокет.
    socket.connect("127.0.0.1", 3000);  // Подключаемся к серверу по заданному порту.
    
    sf::Packet packet;  // Создаём пакет для общения клиента с сервером.
    std::vector<Ball> balls(2);  // Инициализируем начальное положение объектов на карте, принимая данные от сервера.
    for (auto &ball : balls) {  // Пробегаем по всем шарам. На 1 шар 1 пакет.
        socket.receive(packet);  // Получаем пакет.
        packet >> ball;  // Записываем данные из пакета в текущую структуру шара.
        packet.clear();

        std::cout << ball.x << ' ' << ball.y << ' ' << ball.color << '\n';  // Дебаг.
    }

    // отрисуем окно c белым цветом
    sf::RenderWindow window(sf::VideoMode(320, 420), "Squid game");
    window.clear(sf::Color::White);

    // отрисуем мячик с начальными координатами
    sf::CircleShape circle;
    for (auto &ball : balls) {
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
        std::cout << dir << '\n';  // Дебаг

        // Отрисовываем все мячи у каждого пользователя
        // получаем обработанные(обновлённые) данные с сервера
        window.clear(sf::Color::White);
        for (int i = 0; i < balls.size(); ++i) {
            socket.receive(packet);
            packet >> balls[i];
            packet.clear();
            std::cout << balls[i].x << ' '<< balls[i].y << ' ' << balls[i].color << '\n';
            circle.setPosition(balls[i].x, balls[i].y);
            window.draw(circle);
        }
        window.display();
    }
    return 0;
}