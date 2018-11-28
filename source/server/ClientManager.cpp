#include <thread>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "ClientManager.hpp"

using boost::property_tree::ptree;

ClientManager::ClientManager(UdpServer *udpServer, std::size_t &bytesTransferred)
    : _udpServer(udpServer), _bytesTransferred(bytesTransferred)
{
    _clientMessage = _udpServer->getBuffer();
    std::cout << "Dans construc : " << _clientMessage << std::endl;
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
    std::map<udp::endpoint, Client> clients = _udpServer->getClients();

    _udpServer->addClient(Client(_clientEndpoint.address().to_string(), _clientEndpoint.port(), _clientEndpoint));
    _udpServer->_socket.async_send_to(boost::asio::buffer("Lobbies list\n"), _clientEndpoint,
    [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
    });
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
        });
        return false;
    }
    return true;
}

void    ClientManager::manageLobbies()
{
    if (isLobbyCommand() == true) {
        long unsigned int pos = std::string::npos;
        unsigned int it;

        for (it = 0; it < 4 && pos == std::string::npos; it++)
            pos = _clientMessage.find(_lobbyCommands[it]);
        if (pos == std::string::npos)
            _udpServer->_socket.async_send_to(boost::asio::buffer("UNKNOWN COMMAND\n"), _clientEndpoint,
            [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
            });
        else
            ((*this).*_lobbyFunctions.at(it - 1))();
    }
}

void    ClientManager::lobbiesInfo()
{
    std::map<std::string, Lobby>    lobbies = _udpServer->getLobbies();
    boost::property_tree::ptree   pt;
    boost::property_tree::ptree   lobbyInfo;
    boost::property_tree::ptree   allInfo;
    std::ostringstream  oss(std::ostringstream::ate);

    for (std::map<std::string, Lobby>::iterator it = lobbies.begin();
        it != lobbies.end(); it++) {
        lobbyInfo.put("lobbyName", it->second.getName());
        lobbyInfo.put("clientNb", it->second.getNbClients());
        lobbyInfo.put("level", it->second.getLevel());
        allInfo.push_back(std::make_pair("", lobbyInfo));
        lobbyInfo.clear();
    }
    pt.add_child("lobbies", allInfo);
    write_json(oss, pt);
    _udpServer->_socket.async_send_to(boost::asio::buffer(oss.str()), _clientEndpoint,
            [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
            });
}

void    ClientManager::createLobby()
{
    std::map<std::string, Lobby>    lobbies = _udpServer->getLobbies();
    std::string message;
    std::string lobbyInfo = _clientMessage.substr(_clientMessage.find("NEW") + 4);
    std::string lobbyName = lobbyInfo.substr(0, lobbyInfo.find(" "));
    std::string lobbyLevel;

    if (lobbyInfo.find(" ") + 1 < lobbyInfo.size()) {
        lobbyLevel = lobbyInfo.substr(lobbyInfo.find(" "));
        std::cout << "lobbyLevel = " << lobbyInfo << std::endl;
        if (std::atoi(lobbyLevel.c_str()) <= 0 || isNameTaken(lobbyName) == true)
            message = "ERROR\n";
        else {
            _udpServer->addLobby(Lobby(lobbyName, _udpServer->getClient(_clientEndpoint), std::atoi(lobbyLevel.c_str())));
            _udpServer->changeClientStatus(true);
            message = "OK\n";
        }
    }
    else
        message = "UNKNOW COMMAND\n";
    _udpServer->_socket.async_send_to(boost::asio::buffer(message), _clientEndpoint,
        [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
        });
}

void    ClientManager::joinLobby()
{
    std::map<std::string, Lobby>    lobbies = _udpServer->getLobbies();
    std::string message = "ERROR\n";
    std::string lobbyName = _clientMessage.substr(_clientMessage.find("JOIN") + 5);

    if (isNameTaken(lobbyName) == true && clientsInLobby(lobbyName) < 4) {
        message = "OK\n";
        _udpServer->addClientInLobby(lobbyName, _clientEndpoint);
    }
    _udpServer->_socket.async_send_to(boost::asio::buffer(message), _clientEndpoint,
        [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
        });
}

void    ClientManager::setStart()
{
    std::string clientStatus = _clientMessage.substr(_clientMessage.find("LOBBY") + 6);
    bool    inLobby = isClientInLobby();
    bool    readyStatus;
    Lobby   clientLobby;
    std::string message = "ERROR\n";
    unsigned int    it = 0;

    if ((inLobby == true && clientStatus.compare("READY") == 0) ||
        (inLobby == true && clientStatus.compare("UNREADY") == 0)) {
            message = "OK\n";
            if (clientStatus.compare("READY") == 0)
                readyStatus = true;
            else
                readyStatus = false;
            _udpServer->changeClientStatus(readyStatus);
    }
    _udpServer->_socket.async_send_to(boost::asio::buffer(message), _clientEndpoint,
        [] (const boost::system::error_code &error, std::size_t bytesTransferred) {
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