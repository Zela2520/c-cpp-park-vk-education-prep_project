#include "connection.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");							// Поддержка кириллицы в консоли Windows
    // sf::IpAddress ip = sf::IpAddress::getLocalAddress();	//Локальный ip Адресс
    sf::TcpSocket socket;//программный интерфейс для обеспечения обмена данными между процессами
    sf::Packet packet;	//Для осуществления пакетной передачи дынных
    char type;
    char mode = ' ';//Мод s- сервер, с - клиент
    int x = 0;      //координаты шара
    int y = 0;
    char buffer[2000];
    size_t received;	//??
    std::string text = "connect to: ";

//***********Подключение***************//
    std::cout << ip << std::endl;
    std::cout << "Введите тип подключения:  c -клиент, s -сервер" << std::endl;
    std::cin >> type;
    if(type == 's') {
        sf::TcpListener listener;
        listener.listen(2000);
        listener.accept(socket);    //который будет содержать новое соединение
        text += "Server";
        mode = 's';

    } else if(type == 'c'){
        std::cout << "new ip:";
        std::cin >> ip;

        socket.connect(ip, 2000); //ip и Порт
        text += "client";
        mode = 'r';
    }
    socket.send(text.c_str(), text.length() + 1);
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << buffer << std::endl;



//**********Отрисовка Формы***********************//
    sf::RenderWindow window(sf::VideoMode(800, 600), "Network");//Создаем размер Главного окна
    //*******Элементы********************//
    sf::CircleShape shape(10);     //создаем шар с радиусом 50

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed){
                window.close();
            }


        }
        if(mode == 's'){
            socket.receive(packet);				//Команда которая ожидает данных в виде пакета от клиентской части
            if(packet >> x >> y){				//вытаскиваем значение из пакета в переменную x и у (действие уже происходит)
                std::cout << x << ":" << y<< std::endl; 	//..и если все прошло успешно то выводим её координаты
            }
        }

        if(mode == 'r'){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { //первая координата Х отрицательна =>идём влево
                x ++;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { //первая координата Х отрицательна =>идём влево
                x --;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { //первая координата Х отрицательна =>идём влево
                y ++;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { //первая координата Х отрицательна =>идём влево
                y --;
            }

            packet << x << y;		//Пакуем значения координат в Пакет
            socket.send(packet);	//Отправка данных
            packet.clear();			//Чистим пакет
        }
        window.clear();
        shape.setPosition(x, y);	//выставляем шар на координаты
        window.draw(shape);			//отрисовываем шар
        window.display();
        sleep(sf::milliseconds(10));//Задержка
    }//END

    system("pause");
    return 0;
}