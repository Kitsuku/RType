#include "Lobby.hpp"

using boost::asio::ip::udp;

Lobby::Lobby()
{
}

Lobby::Lobby(std::string name, Client master, int level) 
    : _name(name), _level(level)
{
    _clientsInLobby.push_back(master);
    _master = master;
}

std::string Lobby::getName() const
{
    return _name;
}

std::vector<Client> Lobby::getClients() const
{
    return _clientsInLobby;
}

Client  Lobby::getClient(int it)
{
    return _clientsInLobby.at(it);
}

Client  &Lobby::getClient(udp::endpoint clientEndpoint)
{
    unsigned int it;

    for (it = 0; it < _clientsInLobby.size() &&
        _clientsInLobby.at(it).getEndpoint() != clientEndpoint; it++);
    return _clientsInLobby.at(it);
}

Client  Lobby::getMaster() const
{
    return _master;
}

void    Lobby::addClient(Client client)
{
    _clientsInLobby.push_back(client);
}

int Lobby::getNbClients()
{
    int counter = 0;

    for (std::vector<Client>::iterator it = _clientsInLobby.begin();
    it != _clientsInLobby.end(); it++, counter++);
    return counter;
}

void    Lobby::setClientReady(udp::endpoint clientEndpoint, bool status)
{
    getClient(clientEndpoint).setReady(status);
}

int Lobby::getLevel() const
{
    return _level;
}