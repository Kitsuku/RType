#include <functional>
#include <boost/property_tree/ptree.hpp>
#include "UdpServer.hpp"
#include "ClientManager.hpp"

using boost::asio::ip::udp;

UdpServer::UdpServer(boost::asio::io_service &io_service)
    : _socket(io_service, udp::endpoint(udp::v4(), 13)) {
        startReceive();
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
		startReceive();
	});
}