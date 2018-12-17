#include <functional>
#include <thread>
#include <chrono>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "UdpServer.hpp"
#include "ClientManager.hpp"

#include "GameEngine.hpp"
#include "SfmlDisplay.hpp"
#include "ScriptedComponent.hpp"
#include "SfmlController.hpp"
#include "exception/ComponentException.hpp"
#include "TaskObjective.hpp"
#include "TaskShoot.hpp"
#include "TaskMove.hpp"
#include "SceneApparition.hpp"
#include "SceneLoader.hpp"
#include "Button.hpp"
#include "Rect.hpp"
#include "LobbyScreen.hpp"
#include "Screen.hpp"

using boost::asio::ip::udp;

UdpServer::UdpServer(boost::asio::io_service &io_service)
    : _socket(io_service, udp::endpoint(udp::v4(), 13)), _gameSocket(io_service, udp::endpoint(udp::v4(), 14)) {
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
	std::cout << "dans startReceive()" << std::endl;
	_socket.async_receive_from(boost::asio::buffer(_buffer), _remoteEndpoint,
	[this] (const boost::system::error_code &error, std::size_t bytesTransferred) {
		_buffer[bytesTransferred - 1] = 0;
		if (!error || error == boost::asio::error::message_size)
			ClientManager manager(this, bytesTransferred);

		
		// Print de debug
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
			_gameLock.lock();
			// check le move du joueur, le faire bouger et envoyer sa nouvelle pos
			_gameBuffer[bytesTransferred - 1] = 0;
			std::cout << "Message = " << _gameBuffer << std::endl;
			_gameSocket.async_send_to(boost::asio::buffer("BIEN RECU CHEF\n"), _gameRemoteEndpoint,
			[] (const boost::system::error_code &error, std::size_t bytesTransferred) {
			});
			_gameLock.unlock();
			catchPlayerMovement();
		});
}

void	UdpServer::moveComponents()
{
	while (true) {
		for (unsigned int it = 0; it < _games.size(); it++) {
			std::cout << "Je dois move les vaisseaux de la game " << it << std::endl;
		}
	}
}

void	UdpServer::addGame()
{
	Lobby clientLobby = getClientLobby();
	std::vector<Client>	clients = clientLobby.getClientsForGame();

	// Code tempo pour init une game (playScene sera normalement suffisant à la fin)

	//Engine::SfmlDisplay *disp = new Engine::SfmlDisplay;
	Engine::GameEngine engine;
	Engine::ScriptObject script;
	Engine::SceneApparition	a, b, c, d, e, last;
	Engine::ScriptObject so;
	std::vector<std::string> paths = {"Plane.so", "Alien.so"};

	a.actor.actor = 0;
	b.actor.actor = 0;
	c.actor.actor = 1; c.delta = 1000; c.actor.transform.place(Engine::Vector(800, 600));
	d.actor.actor = 0; d.delta = 2000; d.actor.transform.place(Engine::Vector(800, 800));
	e.actor.actor = 0; e.delta = 5000; e.actor.objective = true;
	last.actor.actor = -1; last.delta = -1;
	std::ofstream	f;
	f.open("plop.scn", std::ios::binary);
	setActor(f, paths);
	appear(f, a);
	appear(f, b);
	so.addTask(std::make_unique<Engine::TaskShoot>(Engine::Vector(0, 600)));
	so.addTask(std::make_unique<Engine::TaskShoot>(Engine::Vector(0, 600)));
	so.addTask(std::make_unique<Engine::TaskShoot>(Engine::Vector(0, 600)));
	//so.addTask(std::make_unique<Engine::TaskObjective>(Engine::Vector(100,100)));
	//so.addTask(std::make_unique<Engine::TaskMove>(Engine::Vector(7,8)));
	appear(f, c, &so);
	appear(f, d);
	//so.addTask(std::make_unique<Engine::TaskObjective>(Engine::Vector(3,3)));
	appear(f, e, &so);
	appear(f, e);
	appear(f, last);
	f.close();

	// code à garder
	engine.open();
	
	// Boucle pour créer les vaisseaux joueurs
	
	for (unsigned int it = 0; it < clients.size(); it++) {
		std::unique_ptr<Engine::Component> compo = std::make_unique<Engine::Component>(engine, true);
		//Engine::Component	compo(engine, true);

		std::cout << "compo id = " << compo.get()->getID() << std::endl;
		clients.at(it).setId(compo.get()->getID());
		engine.addComponent(std::move(compo));
		//engine.addComponent(std::make_unique<Engine::Component>(engine, true));
		std::cout << "Nouveau vaisseau allié avec ID = " << clients.at(it).getId() << std::endl;
	}

	sleep(2);
	std::thread launchScene([&engine] () {
		engine.playScene("plop.scn");
	});

	launchScene.detach();

	std::cout << "apres playscene" << std::endl;

	// Fin code tempo et code à garder
	Game	game(clients, clientLobby.getLevel(), engine);

	_games.push_back(game);

	// send infos aux joueurs

	_lobbies.erase(clientLobby.getName());
}

void	UdpServer::deleteLobby(std::string name)
{
	_lobbies.erase(name);
}

// Fonctions temp, à delete une fois les scenes déjà crées

void	UdpServer::setActor(std::ostream &stream, const std::vector<std::string> &path)
{
	unsigned int size = path.size();

	stream.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (const auto &p : path) {
		size = p.size();
		stream.write(reinterpret_cast<char*>(&size), sizeof(size));
		stream.write(p.c_str(), size);
	}
}

void	UdpServer::appear(std::ostream &s, Engine::SceneApparition &app,
			Engine::ScriptObject *so)
{
	unsigned int	size = 0;
	s.write(reinterpret_cast<char*>(&app.delta), sizeof(app.delta));
	s.write(reinterpret_cast<char*>(&app.actor), sizeof(app.actor));
	if (so != nullptr)
		size = so->size();
	s.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (unsigned int it = 0; it < size; ++it) {
		(*so)[it]->serialize(s);
	}
}