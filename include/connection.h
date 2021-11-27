#ifndef INCLUDE_CONNECTION_H_
#define INCLUDE_CONNECTION_H_
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <queue>

class Connection
{
public:
    Connection();
    virtual ~Connection();
    sf::IpAddress get_ip();
private:
    sf::IpAddress ip;
    sf::TcpSocket socket;
    sf::Packet packet;
    int dx;
    int dy;
    size_t received_data; // данные которые пришли действительно
    char buffer[2000];
};

class Server : public Connection {
private:
    sf::TcpListener listener;
};

class Client : public Connection {
};

/*class Connection
{
public:
    Connection();
    virtual ~Connection();
    void run();
    void stop();
    void wait();
    bool pollEvent(sf::Packet& event);
    bool pollEvent(packet::NetworkEvent*& event);
    void send(sf::Packet& packet);
    void disconnect();
    int id()const;
    virtual sf::IpAddress getRemoteAddress()const = 0;
protected:
    sf::TcpSocket _sockIn;
    sf::TcpSocket _sockOut;
private:
    bool _isRunning;
    void _receive();
    sf::Thread _receiveThread;
    sf::Mutex _receiveMutex;
    std::queue<sf::Packet> _incoming;
    void _send();
    sf::Thread _sendThread;
    sf::Mutex _sendMutex;
    std::queue<sf::Packet> _outgoing;
    static int _numberOfCreations;
    const int _id;
};*/


#endif  // INCLUDE_CONNECTION_H_