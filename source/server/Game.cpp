/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Game methods
*/

#include "Game.hpp"
#include <iostream>

using boost::asio::ip::udp;

Game::Game(std::vector<Client> clients, int level)
    : _clients(clients), _level(level)
{
}

int Game::getLevel() const
{
    return _level;
}

std::vector<Client> Game::getClients() const
{
    return _clients;
}

void    Game::setClientNewEndpoint(udp::endpoint endpoint, Client client) noexcept
{
    for (unsigned int it = 0; it < _clients.size(); it++) {
        if (_clients.at(it).getEndpoint() == client.getEndpoint()) {
            _clients.at(it).setEndpoint(endpoint);
            std::cout << "endpoint dans game set" << std::endl;
        }
    }
}

void    Game::launchGame(std::string scene) noexcept
{
    _gameEngine.playScene(scene, EngineDura(0.1));
}

void    Game::translate(std::ostringstream &stream) noexcept
{
    _gameEngine.translater->pushActions(stream);
}
