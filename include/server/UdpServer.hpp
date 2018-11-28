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

		udp::socket _socket;

	private:
		void startReceive();

		udp::endpoint _remoteEndpoint;
		char _buffer[1000];
		std::map<udp::endpoint, Client>	_clients;
		std::mutex _lock;
		std::map<std::string, Lobby>	_lobbies;
	};

#endif /* UDPSERVER_HPP */
