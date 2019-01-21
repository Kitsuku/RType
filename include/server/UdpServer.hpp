//
// EPITECH PROJECT, 2019
// RType
// File description:
// UdpServer class declaration
//

#ifndef UDPSERVER_HPP
	# define UDPSERVER_HPP

	#define BUFFSIZE (1000)

	#include <ctime>
	#include <iostream>
	#include <string>
	#include <memory>
	#include <map>
	#include <thread>
	#include <mutex>
	#include <boost/asio.hpp>
	#include <array>
	#include "Client.hpp"
	#include "Lobby.hpp"
	#include "Game.hpp"
	#include "GameEngine.hpp"

	using boost::asio::ip::udp;

	class UdpServer	{
	public:
		UdpServer(boost::asio::io_service &);
		void	setLock(std::string);

		const udp::endpoint	getEndpoint() const;
		const std::string getBuffer() const;
		const std::map<udp::endpoint, Client>	getClients() const;
		const std::map<std::string, Lobby>	getLobbies() const;
		const Client	getClient(udp::endpoint) const;
		const Lobby	getLobby(std::string) const;	
		void	setClients(std::map<udp::endpoint, Client>);
		void	addClient(Client);
		void	addLobby(Lobby);
		void	addClientInLobby(std::string, udp::endpoint);
		Lobby	getClientLobby();
		void	changeClientStatus(bool);
		int		getClientId() const;
		void	incrClientId();
		bool	clientsAreReady();

		// Game Management
		void	addGame();
		void	gameManagement();
		void	deleteLobby(std::string);
		void	moveComponents();
		void	catchPlayerMovement();

		udp::socket _socket;
		udp::socket	_gameSocket;

	private:
		void	startReceive();
		void	sendMessageInGame(std::string, unsigned int);
		void	clientNewEndpoint() noexcept;
		Game	*getClientGame(Client) noexcept;

		udp::endpoint	_remoteEndpoint;
		udp::endpoint	_gameRemoteEndpoint;
		std::array<char, BUFFSIZE> 	_buffer;
		std::array<char, BUFFSIZE>	_gameBuffer;
		std::map<udp::endpoint, Client>	_clients;
		std::mutex	_lock;
		std::mutex	_gameLock;
		std::map<std::string, Lobby>	_lobbies;
		std::vector<Game>	_games;
		Engine::GameEngine	_gameEngine;
		int	_clientId = 0;
	};

#endif /* UDPSERVER_HPP */
