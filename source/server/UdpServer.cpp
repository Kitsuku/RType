/*
** EPITECH PROJECT, 2019
** RType
** File description:
** UdpServer methods
*/

#include <functional>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <utility>
#include "UdpServer.hpp"
#include "ClientManager.hpp"
#include "IComponent.hpp"
#include "Translater.hpp"
#include "ColliderStatic.hpp"

using boost::asio::ip::udp;

UdpServer::UdpServer(boost::asio::io_service &io_service)
    : _socket(io_service, udp::endpoint(udp::v4(), 13)), _gameSocket(io_service, udp::endpoint(udp::v4(), 14))
{
	std::thread	gameThread([this] () {
		_gameSocket.non_blocking(true);
		_gameSocket.native_non_blocking(true);
		this->gameManagement();
	});
	std::thread	lobbyThread([this] () {
		_socket.non_blocking(true);
    	_socket.native_non_blocking(true);
    	this->startReceive();
	});
	lobbyThread.join();
	gameThread.join();
}

const udp::endpoint	UdpServer::getEndpoint() const
{
	return _remoteEndpoint;
}

const char	*UdpServer::getBuffer() const
{
	return _buffer;
}

const std::map<udp::endpoint, Client>	UdpServer::getClients() const
{
	return _clients;
}

const Client	UdpServer::getClient(udp::endpoint endpoint) const
{
	return _clients.at(endpoint);
}

void	UdpServer::setClients(std::map<udp::endpoint, Client> clients)
{
	_clients = clients;
}

void	UdpServer::addClient(Client client)
{
	_clients[client.getEndpoint()] = client;
}

void	UdpServer::addLobby(Lobby lobby)
{
	_lobbies[lobby.getName()] = lobby;
}

void	UdpServer::addClientInLobby(std::string lobbyName, udp::endpoint clientEndpoint)
{
	std::map<std::string, Lobby>::iterator	it = _lobbies.find(lobbyName);
	Client	client = getClient(clientEndpoint);

	it->second.addClient(client);
}

const std::map<std::string, Lobby>	UdpServer::getLobbies() const
{
	return _lobbies;
}

const Lobby	UdpServer::getLobby(std::string lobbyName) const
{
	return _lobbies.at(lobbyName);
}

Lobby	UdpServer::getClientLobby()
{
	bool    isEnd = false;
    Lobby   clientLobby;

    for (std::map<std::string, Lobby>::iterator itL = _lobbies.begin();
        itL != _lobbies.end() && isEnd == false; itL++) {
            for (unsigned int it = 0; it < itL->second.getClients().size(); it++)
                if (itL->second.getClient(it).getEndpoint() == _remoteEndpoint) {
                    isEnd = true;
                    clientLobby = itL->second;
                }
    }
    return clientLobby;
}

void	UdpServer::changeClientStatus(bool status)
{
	Lobby	clientLobby = getClientLobby();

	_lobbies.find(clientLobby.getName())->second.getClient(_remoteEndpoint).setReady(status);
}

void	UdpServer::setLock(std::string action)
{
	if (action == "lock")
		_lock.lock();
	else
		_lock.unlock();
}

void	UdpServer::startReceive()
{
	_socket.async_receive_from(boost::asio::buffer(_buffer), _remoteEndpoint,
	[this] (const boost::system::error_code &error, std::size_t bytesTransferred) {
		_buffer[bytesTransferred - 1] = 0;
		if (!error || error == boost::asio::error::message_size)
			ClientManager manager(this, bytesTransferred);

		// Activité sur le serveur

		std::cout << "J'ai actuellement " << _clients.size() << " clients de co" << std::endl;
		for (std::map<udp::endpoint, Client>::iterator it = _clients.begin(); it != _clients.end(); it++)
			std::cout << it->second.getAddress() << " " << std::to_string(it->second.getPort()) << std::endl;

		std::cout << "Et voici mes lobby:" << std::endl;
		for (std::map<std::string, Lobby>::iterator it = _lobbies.begin(); it != _lobbies.end(); it++) {
			std::cout << "- " << it->second.getName() << std::endl;
			std::vector<Client> lobbyClients = it->second.getClients();
			for (unsigned int itC = 0; itC < lobbyClients.size(); itC++) {
				std::cout << "    - " << lobbyClients.at(itC).getAddress() << " " << lobbyClients.at(itC).getPort();
				if (lobbyClients.at(itC).getReady() == true)
					std::cout << " : ce client est ready" << std::endl;
				else
					std::cout << " : ce client n'est pas ready" << std::endl;
			}
		}

		std::cout << "Il y a " << _games.size() << " games en cours." << std::endl;
		std::cout << std::endl << std::endl;

		// Fin print

		startReceive();
	});
}

void	UdpServer::incrClientId()
{
	_clientId += 1;
}

int	UdpServer::getClientId() const
{
	return _clientId;
}

bool	UdpServer::clientsAreReady()
{
	Lobby	clientLobby = getClientLobby();
	std::vector<Client>	clients = clientLobby.getClients();

	for (unsigned int it = 0; it < clients.size(); it++) {
		if (clients.at(it).getReady() == false)
			return false;
	}
	return true;
}

void	UdpServer::gameManagement()
{
	std::thread	playerMove([this] () {
		this->catchPlayerMovement();
	});
	std::thread	moveAll([this] () {
		this->moveComponents();
	});

	playerMove.detach();
	moveAll.detach();
}

void	UdpServer::catchPlayerMovement()
{
	_gameSocket.async_receive_from(boost::asio::buffer(_gameBuffer), _gameRemoteEndpoint,
		[this] (const boost::system::error_code &code, std::size_t bytesTransferred) {
			_gameBuffer[bytesTransferred - 1] = 0;
			std::cout << "gameBuffer = " << _gameBuffer << std::endl;
			if (!code && bytesTransferred > 0) {
				_gameLock.lock();
				if (_clients.find(_gameRemoteEndpoint) == _clients.end())
					clientNewEndpoint();
				_gameLock.unlock();
			}
			catchPlayerMovement();
		});
}

void	UdpServer::moveComponents()
{
	std::string	message;

	while (true) {
		for (unsigned int it = 0; it < _games.size(); it++) {
			sleep(1);
			/*std::ostringstream stream;
			std::cout << "avant translate" << std::endl;
			//_games.at(it).translate(stream);
			_gameEngine.translater->pushActions(stream);
			//std::cout << "apres translate" << std::endl;
			//std::cout << "stream content = " << stream.str() << std::endl;
			//stream << "Bonjour";
			message = stream.str() + "\n";
			sendMessageInGame(message, it);
			//message.clear();
			//stream.clear();*/
		}
	}
}

void	UdpServer::addGame()
{
	Lobby clientLobby = getClientLobby();
	std::vector<Client>	clients = clientLobby.getClientsForGame();
	//Engine::ColliderStatic	*box = new Engine::ColliderStatic(Engine::Vector(0, 0),
	//							Engine::Vector(1200, 1000));
	Game	game(clients, clientLobby.getLevel());

	//game.launchGame("level00.scn");
	_games.push_back(std::move(game));
	_lobbies.erase(clientLobby.getName());
	//std::cout << "befooooore" << std::endl;
	//_gameEngine.setBoundingBox(box);
	//_gameEngine.open();
	//_gameEngine.playScene("level00.scn", EngineDura(0.1));
	//std::cout << "aftereererere" << std::endl;
}

void	UdpServer::deleteLobby(std::string name)
{
	_lobbies.erase(name);
} 

void    UdpServer::sendMessageInGame(std::string information, unsigned int gameNb)
{
	const std::vector<Client>	clients = _games.at(gameNb).getClients();

	for (unsigned int itC = 0; itC < clients.size(); itC++) {
		std::cout << "envoie d'un message au client id = " << clients.at(itC).getId() << std::endl;
		_gameSocket.async_send_to(boost::asio::buffer(information), clients.at(itC).getEndpoint(),
		[information] (const boost::system::error_code &error, std::size_t bytesTransferred) {
			if (!error || bytesTransferred == 0)
				std::cerr << "Error in sendMessageInGame" << std::endl;
        });
	}
}

Game	*UdpServer::getClientGame(Client client) noexcept
{
	for (unsigned int it = 0; it < _games.size(); it++) {
		std::vector<Client>	clientsInGame = _games.at(it).getClients();

		for (unsigned int itC = 0; itC < clientsInGame.size(); itC++)
			if (client.getEndpoint() == clientsInGame.at(itC).getEndpoint())
				return &(_games.at(it));
	}
	return nullptr;
}

void	UdpServer::clientNewEndpoint() noexcept
{
	if (_gameBuffer[0] != 0) {
		int	clientId = std::stoi(_gameBuffer);
		std::map<udp::endpoint, Client>::iterator it;

		for (it = _clients.begin(); it->second.getId() != clientId && 
			it != _clients.end(); it++);
		if (it != _clients.end()) {
			Client	client = it->second;
			Game	*game = getClientGame(client);
			std::vector<Client>	clientsInGame = game->getClients();

			game->setClientNewEndpoint(_gameRemoteEndpoint, client);
			
			client.setEndpoint(_gameRemoteEndpoint);
			_clients.erase(it);
			_clients[client.getEndpoint()] = client;
		}
	}
}
