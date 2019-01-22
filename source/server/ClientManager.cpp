/*
** EPITECH PROJECT, 2019
** RType
** File description:
** ClientManager methods
*/

#include <thread>
#include "ClientManager.hpp"

ClientManager::ClientManager(UdpServer *udpServer, std::size_t &bytesTransferred)
    : _udpServer(udpServer), _bytesTransferred(bytesTransferred)
{
    _clientMessage = _udpServer->getBuffer();
    _clientEndpoint = _udpServer->getEndpoint();
    initPtr();
    std::thread myThread([this] () {
        this->_udpServer->setLock("lock");
        std::map<udp::endpoint, Client> clients = this->_udpServer->getClients();
        std::map<udp::endpoint, Client>::iterator it = clients.find(this->getEndpoint());
        if (it == clients.end())
            this->addClient();
        else
            this->manageLobbies();
        this->_udpServer->setLock("unlock");
    });
    myThread.join();
}

void    ClientManager::initPtr()
{
    _lobbyCommands.at(0) = "INFO";
    _lobbyCommands.at(1) = "NEW";
    _lobbyCommands.at(2) = "JOIN";
    _lobbyCommands.at(3) = "READY";
    _lobbyFunctions.at(0) = &ClientManager::lobbiesInfo;
    _lobbyFunctions.at(1) = &ClientManager::createLobby;
    _lobbyFunctions.at(2) = &ClientManager::joinLobby;
    _lobbyFunctions.at(3) = &ClientManager::setStart;
}

void    ClientManager::addClient()
{
    std::string message = "ID " + std::to_string(_udpServer->getClientId()) + "\n";

    _udpServer->addClient(Client(_clientEndpoint.address().to_string(), _clientEndpoint.port(), _clientEndpoint, _udpServer->getClientId()));
    _udpServer->_socket.async_send_to(boost::asio::buffer(message), _clientEndpoint,
        [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
            if (error || bytesTransferred == 0)
                std::cerr << "Error when sending a message to client (addClient)" << std::endl;
        });
    _udpServer->incrClientId();
}

udp::endpoint   ClientManager::getEndpoint()
{
    return _clientEndpoint;
}

bool    ClientManager::isLobbyCommand()
{
    if (_clientMessage.find("LOBBY") == _clientMessage.npos) {
        _udpServer->_socket.async_send_to(boost::asio::buffer("UNKNOWN COMMAND\n"), _clientEndpoint,
        [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
            if (error || bytesTransferred == 0)
                std::cerr << "Error when sending a message to client (isLobbyCommand)" << std::endl;
        });
        return false;
    }
    return true;
}

void    ClientManager::manageLobbies()
{
    if (isLobbyCommand() == true) {
        std::size_t pos = _clientMessage.npos;
        unsigned int it;

        for (it = 0; it < 4 && pos == _clientMessage.npos; it++)
            pos = _clientMessage.find(_lobbyCommands[it]);
        if (pos == std::string::npos)
            _udpServer->_socket.async_send_to(boost::asio::buffer("UNKNOWN COMMAND\n"), _clientEndpoint,
            [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
                if (error || bytesTransferred == 0)
                    std::cerr << "Error when sending a message to client (addClient)" << std::endl;
            });
        else {
            ((*this).*_lobbyFunctions.at(it - 1))();
        }
    }
}

void    ClientManager::lobbiesInfo()
{
    std::map<std::string, Lobby>    lobbies = _udpServer->getLobbies();
    std::ostringstream  oss(std::ostringstream::ate);

    oss << lobbies.size();
    for (std::map<std::string, Lobby>::iterator it = lobbies.begin();
        it != lobbies.end(); it++) {
            oss << " " << it->second.getName() << " " << it->second.getNbClients() << " " << it->second.getLevel() << " " << it->second.getMaxPlace();
    }
    oss << std::endl;
    _udpServer->_socket.async_send_to(boost::asio::buffer(oss.str()), _clientEndpoint,
    [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
        if (error || bytesTransferred == 0)
            std::cerr << "Error when sending a message to client (lobbiesInfo)" << std::endl;
    });
}

void    ClientManager::createLobby()
{
    std::map<std::string, Lobby>    lobbies = _udpServer->getLobbies();
    std::string message;
    std::string lobbyInfo = _clientMessage.substr(_clientMessage.find("NEW") + 4);
    std::string lobbyName = lobbyInfo.substr(0, lobbyInfo.find(" "));
    std::string lobbyLevel;
    std::string maxPlace;

    if (lobbyInfo.find(" ") + 1 < lobbyInfo.size()) {
        lobbyLevel = lobbyInfo.substr(lobbyInfo.find(" "));
        maxPlace = lobbyInfo.substr(lobbyInfo.find(" ") + 3);
        if (std::atoi(lobbyLevel.c_str()) <= 0 || isNameTaken(lobbyName) == true ||
            std::atoi(maxPlace.c_str()) <= 0 || std::atoi(maxPlace.c_str()) > 4)
            message = "ERROR\n";
        else {
            _udpServer->addLobby(Lobby(lobbyName, _udpServer->getClient(_clientEndpoint), std::atoi(lobbyLevel.c_str()), std::atoi(maxPlace.c_str())));
            message = "OK\n";
        }
    }
    else
        message = "UNKNOW COMMAND\n";
    _udpServer->_socket.async_send_to(boost::asio::buffer(message), _clientEndpoint,
        [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
            if (error || bytesTransferred == 0)
                std::cerr << "Error when sending a message to client (addClient)" << std::endl;
        });
}

void    ClientManager::joinLobby()
{
    std::map<std::string, Lobby>    lobbies = _udpServer->getLobbies();
    std::string message = "ERROR\n";
    std::string lobbyName = _clientMessage.substr(_clientMessage.find("JOIN") + 5);
    bool    inLobby = isClientInLobby();

    if (isNameTaken(lobbyName) == true && clientsInLobby(lobbyName) < 4
    && inLobby != true) {
        _udpServer->addClientInLobby(lobbyName, _clientEndpoint);
        sendMessageInLobby("JOIN");
        getClientsInLobbyInformations(message);
    }
    _udpServer->_socket.async_send_to(boost::asio::buffer(message), _clientEndpoint,
        [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
            if (error || bytesTransferred == 0)
                std::cerr << "Error when sending a message to client (addClient)" << std::endl;
        });
}

void    ClientManager::setStart()
{
    std::string clientStatus = _clientMessage.substr(_clientMessage.find("LOBBY") + 6);
    bool    inLobby = isClientInLobby();
    bool    readyStatus;
    Lobby   clientLobby;
    std::string message = "ERROR\n";

    if ((inLobby == true && clientStatus.compare("READY") == 0) ||
        (inLobby == true && clientStatus.compare("UNREADY") == 0)) {
            message = "OK\n";
            if (clientStatus.compare("READY") == 0)
                readyStatus = true;
            else
                readyStatus = false;
            _udpServer->changeClientStatus(readyStatus);
            if (_udpServer->clientsAreReady() == true) {
                sendMessageInLobby("GAME START");
                _udpServer->addGame();
                message = "GAME START\n";
            }
            else
                sendMessageInLobby("READY");
    }
    _udpServer->_socket.async_send_to(boost::asio::buffer(message), _clientEndpoint,
        [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
            if (error || bytesTransferred == 0)
                std::cerr << "Error when sending a message to client (addClient)" << std::endl;
        });
}

bool    ClientManager::isClientInLobby()
{
    std::map<std::string, Lobby> lobbies = _udpServer->getLobbies();

    for (std::map<std::string, Lobby>::iterator itL = lobbies.begin();
        itL != lobbies.end(); itL++) {
            for (unsigned int it = 0; it < itL->second.getClients().size(); it++)
                if (itL->second.getClient(it).getEndpoint() == _clientEndpoint)
                    return true;
    }
    return false;
}

bool    ClientManager::isNameTaken(std::string newLobbyName)
{
    std::map<std::string, Lobby>    lobbies = _udpServer->getLobbies();

    if (lobbies.find(newLobbyName) == lobbies.end())
        return false;
    return true;
}

int ClientManager::clientsInLobby(std::string lobbyName)
{
    Lobby   lobby = _udpServer->getLobby(lobbyName);

    return lobby.getNbClients();
}

Lobby   ClientManager::getClientLobby()
{
    std::map<std::string, Lobby> lobbies = _udpServer->getLobbies();
    bool    isEnd = false;
    Lobby   clientLobby;

    for (std::map<std::string, Lobby>::iterator itL = lobbies.begin();
        itL != lobbies.end() && isEnd == false; itL++) {
            for (unsigned int it = 0; it < itL->second.getClients().size(); it++)
                if (itL->second.getClient(it).getEndpoint() == _clientEndpoint) {
                    isEnd = true;
                    clientLobby = itL->second;
                }
    }
    return clientLobby;
}

void    ClientManager::sendMessageInLobby(std::string information)
{
    Lobby lobby = _udpServer->getClientLobby();
    std::vector<Client> clients = lobby.getClients();
    Client  currentClient = _udpServer->getClient(_clientEndpoint);
    std::string message = "LOBBY " + std::to_string(currentClient.getId()) + " " + information + "\n";

    for (unsigned int it = 0; it < clients.size(); it++) {
        if (clients.at(it).getEndpoint() != _clientEndpoint) {
            _udpServer->_socket.async_send_to(boost::asio::buffer(message), clients.at(it).getEndpoint(),
            [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
                if (error || bytesTransferred == 0)
                    std::cerr << "Error when sending a message to client (addClient)" << std::endl;
            });
        }
    }
}

void    ClientManager::getClientsInLobbyInformations(std::string &message)
{
    Lobby   lobby = _udpServer->getClientLobby();
    std::vector<Client> clients = lobby.getClients();

    message = std::to_string(clients.size() - 1);
    for (unsigned int it = 0; it < clients.size(); it++) {
        if (clients.at(it).getEndpoint() != _clientEndpoint) {
            message += " " + std::to_string(clients.at(it).getId());
            if (clients.at(it).getReady() == true)
                message += " READY";
            else
                message += " UNREADY";
        }
    }
    message += "\n";
}
