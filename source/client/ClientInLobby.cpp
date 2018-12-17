#include "ClientInLobby.hpp"

ClientInLobby::ClientInLobby()
{
}

ClientInLobby::ClientInLobby(int id, bool ready)
    : _id(id), _ready(ready)
{
}

ClientInLobby::ClientInLobby(int id) : _id(id)
{
    _ready = false;
}

bool    ClientInLobby::isReady() const
{
    return _ready;
}

void    ClientInLobby::setReady(bool ready)
{
    _ready = ready;
}

int ClientInLobby::getId() const
{
    return _id;
}

void    ClientInLobby::changeStatus()
{
    if (_ready == true)
        _ready = false;
    else
        _ready = true;
}