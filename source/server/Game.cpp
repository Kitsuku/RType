#include "Game.hpp"

Game::Game(std::vector<Client> clients, int level)
    : _clients(clients), _level(level)
{
}

int Game::getLevel() const
{
    return _level;
}