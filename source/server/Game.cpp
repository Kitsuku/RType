#include "Game.hpp"

Game::Game(std::vector<Client> clients, int level,
        Engine::GameEngine &engine)
    : _clients(clients), _level(level), _engine(engine)
{
}

int Game::getLevel() const
{
    return _level;
}