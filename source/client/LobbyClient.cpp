#include "LobbyClient.hpp"

LobbyClient::LobbyClient()
{
}

LobbyClient::LobbyClient(std::string name, int clientsNb, int level, int maxPlace)
    : _name(name), _clientsNb(clientsNb), _level(level), _maxPlace(maxPlace)
{
}

std::string LobbyClient::getName() const
{
    return _name;
}

int LobbyClient::getNbClients() const
{
    return _clientsNb;
}

int LobbyClient::getLevel() const
{
    return _level;
}

int LobbyClient::getMaxPlace() const
{
    return _maxPlace;
}

void    LobbyClient::changeClientStatus(int clientId)
{
    for (unsigned int it = 0; it < _clients.size(); it++) {
        if (_clients.at(it).getId() == clientId)
            _clients.at(it).changeStatus();
    }
}

void    LobbyClient::addClient(int clientId)
{
    _clients.push_back(ClientInLobby(clientId));
}

void    LobbyClient::addClient(int clientId, bool ready)
{
    _clients.push_back(ClientInLobby(clientId, ready));
}

std::vector<ClientInLobby>  LobbyClient::getClients() const
{
    return _clients;
}