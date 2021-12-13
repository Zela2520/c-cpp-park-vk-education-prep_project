#include "connection.h"

Connection::Connection() :
    ip(sf::IpAddress::getLocalAddress()),
     dx(0),
     dy(0){}
Connection::~Connection() {}

sf::IpAddress Connection::get_ip() {
    return this->ip;
}
/*
void Connection::run()
{
    _isRunning = true;
    _receiveThread.launch();
    _sendThread.launch();
}

void Connection::stop() {
    _isRunning  = false;
}

void Connection::wait()
{
    _receiveThread.wait();
    _sendThread.wait();
}

int Connection::id()const {
    return _id;
}

bool Connection::pollEvent(sf::Packet& event)
{
    bool res = false;
    sf::Lock guard(_receiveMutex);
    if(_incoming.size() > 0)
    {
        std::swap(event,_incoming.front());
        _incoming.pop();
        res = true;
    }
    return res;
}

bool Connection::pollEvent(packet::NetworkEvent*& event)
{
    bool res = false;
    sf::Packet msg;
    if(Connection::pollEvent(msg))
    {
        event = packet::NetworkEvent::makeFromPacket(msg);
        if(event != nullptr)
            res = true;
    }
    return res;
}*/

