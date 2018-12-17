#include <iostream>
#include "Client.hpp"

using boost::asio::ip::udp;

Client::Client()
{
}

Client::Client(std::string address, unsigned short port, udp::endpoint endpoint, int id)
    : _address(address), _port(port), _endpoint(endpoint), _id(id)
{
}

const std::string Client::getAddress() const
{
    return _address;
}

const unsigned short    Client::getPort() const
{
    return _port;
}

void    Client::setMessage(const std::string message)
{
    _message = message;
}

const std::string   Client::getMessage() const
{
    return _message;
}

udp::endpoint   Client::getEndpoint() const
{
    return _endpoint;
}

void    Client::setReady(bool ready)
{
    _isReady = ready;
}

bool    Client::getReady() const
{
    return _isReady;
}

int Client::getId() const
{
    return _id;
}

void    Client::setId(int id)
{
    _id = id;
}