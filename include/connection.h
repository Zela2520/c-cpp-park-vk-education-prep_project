#ifndef INCLUDE_CONNECTION_H_
#define INCLUDE_CONNECTION_H_
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <functional>
#include <mutex>
#include <queue>
#include <vector>

#define MAX_NUMBER_OF_CLIENTS 4

class Server {
private:
    using Cb = std::function<void(sf::TcpSocket)>; // создаём функцию для обработки очередного клиента
    uint16_t port; //  порт на котором будет слушать сервер
    sf::TcpListener listener;
    sf::TcpSocket new_client;
    std::vector<sf::TcpSocket> playing_clients; // количество подключенных клиентов
    std::queue<sf::TcpSocket> waiting_clients; // количество ожидающих клиентов
    std::vector<std::thread> threads; // кооличество потоков равно количеству клиентов
    size_t size_of_threads = MAX_NUMBER_OF_CLIENTS;
    size_t size_of_clients = size_of_threads;
public:
    Server(uint16_t port, Cb) : port(port) {  //  инициализируем порт, по которому будем слушать
        threads.reserve(size_of_threads); // создаём четыре потока
        playing_clients.reserve(size_of_clients); // создаём четырёх игроков
        listener.listen(port); // начинаем слушать порт
        for (auto &socket : playing_clients) {
            if(listener.accept(socket) != sf::Socket::Done) {
                perror("Error socket init");
                exit(EXIT_FAILURE);
            }
        }
        while (1) {
            if (playing_clients.size() < 5) { // если число клиентов меньше пяти, то добавляем клиента в игру
                playing_clients.push_back(new_client);
            } else {
                waiting_clients.emplace(new_client);
            }
        }
    }
    ~Server() = default;
    void game_init(sf::TcpSocket &sock) {
        std::cout << "Hi";
    }
};



/*#include <cstdint>
#include <functional>
#include <thread>
#include <list>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static constexpr uint16_t buffer_size = 4096;

struct TcpServer {
    class Client;

    // callback функция для обработки клиентов
     typedef std::function<void(Client)> handler_function_t;
     // статус сервера
     enum class status : uint8_t {
         up = 0,
         err_socket_init = 1,
         err_socket_bind = 2,
         err_socket_listening = 3,
         close = 4
     };

private:
    uint16_t port;
    status _status = status::close;
    handler_function_t handler;
    std::thread handler_thread;
    std::list<std::thread> clients_handler_threads;
    std::list<std::thread::id> client_handling_end;
    int serv_socket;
    void handling_Loop();


public:
    TcpServer(const uint16_t port, handler_function_t handler);
    ~TcpServer();

    void setHandler(handler_function_t handler);
    uint16_t get_port() const;
    uint16_t set_port(const uint16_t port);
    status get_status() const {return _status;}

    status restart();
    status start();
    void stop();
    void joinLoop();
};

class TcpServer::Client {
public:
    int socket;
    struct sockaddr_in address;
    char buffer[buffer_size];
public:
    Client(int socket, struct sockaddr_in address);
    Client(const Client& other);
    ~Client();

    uint32_t getHost() const;
    uint16_t getPort() const;

    int loadData();
    char* getData();

    bool send_data(const char* buffer, const size_t size) const;
};*/


#endif  // INCLUDE_CONNECTION_H_