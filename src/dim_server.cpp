#include "../include/model.h"



int main(int argc, char* argv[]) {
    sf::TcpListener listener;
    //// Устанавливаем по какому порту будет проходить подключение к серверу
    if (listener.listen(3000) != sf::Socket::Done) {  // Слушаем порт 3000.
        std::cerr << "Error";
    }
    //// Рассмотрим случай для двух клиентов
    std::vector<sf::TcpSocket> clients(2);
    //// если кто-то подключается, то accept индентифицирует клиента для дальнешей работы с ним
    for (auto &socket : clients) {
        listener.accept(socket);
    }


    //// Все используемые в программе текстуры.
    sf::Texture amogusTexture;
    amogusTexture.loadFromFile("../include/textures/amogus.png");

    sf::Texture babyTexture;
    babyTexture.loadFromFile("../include/textures/baby.png");

    sf::Texture gachiTexture;
    gachiTexture.loadFromFile("../include/textures/gachi.png");

    sf::Texture kotTexture;
    kotTexture.loadFromFile("../include/textures/kot.jpg");

    sf::Texture tntTexture;
    tntTexture.loadFromFile("../include/textures/tnt.png");

    sf::Packet packet;  //// Создаём пакет для общения клиента с сервером.

    std::vector<Player> players(clients.size(), Player(0, 0, amogusTexture));  //// Задаём начальное положение массиву игроков.

    std::vector<Unmovable> unmovables(1, Unmovable(200, 200, gachiTexture));   //// Создаём одну стенку.


    //// Заранее отправляем клиентам данные о том, что клиенты расположены на нулевых координатах.
    for (auto &client : clients) {  //// Для каждого клиента.
        for (auto &player : players) {   //// О каждом игроке.
            packet << player;
            client.send(packet);
            packet.clear();
        }
        for (auto &unmovable : unmovables) {   //// И о каждом несдвигаемом объекте.
            packet << unmovable;
            client.send(packet);
            packet.clear();
        }
    }

//// чтобы не привязываться к мощности процессора введём переменную времени
    sf::Clock clock;

    while (true) {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart(); //// обновляем счётчик времени
        time /= 500; //// регулируем скорость игры
        //// Получаем пакет с информацией о перемещении какждого клиента и извлекаем информацию о его перемещении.
        //// Перемещение i-ого клиента значит перемещение i-ого мячика.
        for (int i = 0; i < clients.size(); ++i) {
            clients[i].receive(packet);
            bool directions[4];
            packet >> directions;  //// Достаём информацию из пакета.
            packet.clear();

            //// Обрабатываем полученную информацию о направлении.
            if (directions[0]) {   //// Вверх.
                players[i].goUp(0.3 * time); //// передвигаем персонажа вверх
                if (players[i].intersects_with(unmovables)) players[i].goDown(0.3 * time); //// если произошло пересечение объекта и персогаэа, то отодвигаем его обратно
                //// таким образом объект останется неподвижным
            }
            if (directions[1]) {  //// Направо.
                players[i].goRight(0.3 * time);  //// передвигае0.3 * timeм персонажа вправо
                if (players[i].intersects_with(unmovables)) players[i].goLeft(0.3 * time); //// если произошло пересечение объекта и персогаэа, то отодвигаем его обратно
                //// таким образом объект останется неподвижным
            }
            if (directions[2]) {  //// Вниз.
                players[i].goDown(0.3 * time); //// передвигаем персонажа вниз
                if (players[i].intersects_with(unmovables)) players[i].goUp(0.3 * time); //// если произошло пересечение объекта и персогаэа, то отодвигаем его обратно
                //// таким образом объект останется неподвижным
            }
            if (directions[3]) {  //// Налево.
                players[i].goLeft(0.3 * time); //// передвигаем персонажа влево
                if (players[i].intersects_with(unmovables)) players[i].goRight(0.3 * time); //// если произошло пересечение объекта и персогаэа, то отодвигаем его обратно
                //// таким образом объект останется неподвижным
            }
        }

        //// Отправляем обновлённые данные об изменение всех объектов на сервере каждому клиенту.
        for (auto &client : clients) {  //// Каждому клиенту.
            for (auto &player : players) {    //// О каждом игроке.
                packet << player;  //// Записываем в пакет всю информацию об игроке.
                client.send(packet);
                packet.clear();
            }
            for (auto &unmovable : unmovables) {   //// И о каждом несдвигаемом объекте.
                packet << unmovable;
                client.send(packet);
                packet.clear();
            }
        }
    }
    return 0;
}

