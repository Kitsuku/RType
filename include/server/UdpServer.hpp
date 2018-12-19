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
	#include "Client.hpp"
	#include "Lobby.hpp"
	#include "Game.hpp"

	using boost::asio::ip::udp;

	class UdpServer	{
	public:
		UdpServer(boost::asio::io_service &);
		void	setLock(std::string);

		const udp::endpoint	getEndpoint() const;
		const char	*getBuffer() const;
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
		void startReceive();

		udp::endpoint	_remoteEndpoint;
		udp::endpoint	_gameRemoteEndpoint;
		char _buffer[1000];
		char	_gameBuffer[1000];
		std::map<udp::endpoint, Client>	_clients;
		std::mutex	_lock;
		std::mutex	_gameLock;
		std::map<std::string, Lobby>	_lobbies;
		std::vector<Game>	_games;
		int	_clientId = 0;
	};

#endif /* UDPSERVER_HPP */
