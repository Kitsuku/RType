#include <iostream>
#include <fstream>
#include <exception>
#include <boost/throw_exception.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>

#include "UdpClient.hpp"
#include "LobbyClient.hpp"

using boost::asio::ip::udp;
using boost::asio::deadline_timer;

UdpClient::UdpClient(std::string host, std::string port, boost::asio::io_service &io)
    : _socket(io), _host(host), _io(io)
{
    std::cout << "host = " << host << " et port = " << port << std::endl;
    _inLobby = false;
    _ready = false;
    _inGame = false;
}

void    UdpClient::setSendMessage(const std::string message) noexcept
{
    _sendMessage = message;
}

void    UdpClient::start(udp::resolver::iterator endpointIt)
{
    _socket.open(udp::v4());
    _socket.non_blocking(true);
    _socket.native_non_blocking(true);
    startConnect(endpointIt);
}

void    UdpClient::startConnect(udp::resolver::iterator endpointIt)
{
    if (endpointIt != udp::resolver::iterator()) {
        std::cout << "Trying " << endpointIt->endpoint() << "..." << std::endl;
        _socket.async_connect(endpointIt->endpoint(),
        [this, endpointIt] (const boost::system::error_code &code) {
            udp::resolver::iterator endIt = endpointIt;
            if (!_socket.is_open()) {
                std::cout << "Connection ended" << std::endl;
                startConnect(++endIt);
            }
            else if (code) {
                _socket.close();
                startConnect(++endIt);
            }
            else if (!code) {
                std::cout << "Connected to " << endpointIt->endpoint() << std::endl;
                _serverEndpoint = *endpointIt;
                if (_inGame == true)
                    _sendMessage = "GAME SERVER JOINED";
                else
                    _sendMessage = "NOUVEAU CLIENT";
                //startWrite();
                _socket.send_to(boost::asio::buffer(_sendMessage), _serverEndpoint);
                makeClientReadWrite();
                std::cout << "The end?" << std::endl;
            }
        });
    }
}

void    UdpClient::makeClientReadWrite() noexcept
{
    /*std::thread clientRead([this] {
        std::cout << "read thread" << std::endl;
        sleep(0.2);
        this->startRead();
    });
    clientRead.join();*/

    startRead();
    std::thread clientWrite([this] {
        this->startWrite();
    });
    clientWrite.detach();
}

void    UdpClient::startWrite()
{
    static  bool    firstWrite = true;

    if (firstWrite == true) {
        firstWrite = false;
        sleep(1);
    }
    if (_isConnected == false)
        return;
    while (_sendMessage.empty() == true);
    if (_sendMessage != "") {
        _sendMessage += "\n";
        std::cout << "Avant fail" << std::endl;
        _socket.send_to(boost::asio::buffer(_sendMessage), _serverEndpoint);
        std::cout << "Apres" << std::endl;
    }
    sleep(0.3);
    startWrite();
}

/*void    UdpClient::startWrite()
{
    if (_sendMessage != "") {
        _sendMessage += "\n";
        std::cout << "Le message est " << _sendMessage;
        _socket.send_to(boost::asio::buffer(_sendMessage), _serverEndpoint);
    }
    if (_isReading != true) {
        _isReading = true;
        std::thread clientRead([this] {
            this->startRead();
        });
        clientRead.detach();
    }
    startWrite();
}*/

void    UdpClient::startRead()
{
    //std::cout << "en attente de quelque chose à read" << std::endl;
    _socket.async_receive_from(boost::asio::buffer(_receiveMessage), _serverEndpoint,
    boost::bind(&UdpClient::handleReceive, this, boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

void    UdpClient::handleReceive(const boost::system::error_code& error, size_t bytes_transferred) {
    //std::cout << "Dans handle" << std::endl;
    if (error) {
        std::cout << "Receive failed: " << error.message() << "\n";
        _isConnected = false;
        return;
    }
    _receiveMessage.at(bytes_transferred - 1) = 0;
    //std::cout << "Received: '" << _receiveMessage.data() << "' (" << error.message() << ")\n";
    if (_firstMessage == true) {
        getMyId();
        _firstMessage = false;
        _sendMessage = "";
    }
    manageReceiveMessage();
}

void    UdpClient::getMyId()
{
    std::string message = _receiveMessage.data();

    message.erase(0, message.find(" ") + 1);
    _myId = std::atoi(message.c_str());
    std::cout << "Mon id est:" << message << std::endl;
}

const LobbyClient   &UdpClient::getLobbyClient() const noexcept
{
    return _myLobby;
}

std::map<std::string, LobbyClient>      &UdpClient::getLobbies() noexcept
{
    return _lobbies;
}

void    UdpClient::manageReceiveMessage()
{
    std::string message = _receiveMessage.data();
    if (message.find("LOBBY") != message.npos) {
        manageMyLobby();
        startRead();
    } else if (_sendMessage.find("LOBBY INFO") != _sendMessage.npos)
        setLobbies();
    else if (_sendMessage.find("LOBBY JOIN") != _sendMessage.npos)
        checkJoin();
    else if (_sendMessage.find("LOBBY NEW") != _sendMessage.npos)
        checkCreate();
    if (message.find("GAME START") != message.npos) {
        _socket.close();
        _inGame = true;
        udp::resolver resolver(_io);
        std::cout << "Je dois start la game" << std::endl;
        start(resolver.resolve(udp::resolver::query(udp::v4(), _host, std::to_string(14))));
    }
    startRead();
}

void    UdpClient::manageMyLobby()
{
    std::string message = _receiveMessage.data();
    int clientId;
    
    message.erase(0, 6);
    clientId = std::atoi(message.substr(0, message.find(" ")).c_str());
    message.erase(0, message.find(" ") + 1);
    if (message == "JOIN")
        _myLobby.addClient(clientId);
    else if (message == "READY")
        _myLobby.changeClientStatus(clientId);
    
    std::cout << "Dans le lobby où je suis (" << _myLobby.getName() << "):" << std::endl;
    std::vector<ClientInLobby>  clients = _myLobby.getClients();
    for (unsigned int it = 0; it < clients.size(); it++) {
        std::cout << "- " << clients.at(it).getId() << " is ";
        if (clients.at(it).isReady() == true)
            std::cout << "ready" << std::endl;
        else
            std::cout << " not ready" << std::endl;
    }
}

void    UdpClient::defineAction()
{
    getline(std::cin, _sendMessage);
    startWrite();
}

void    UdpClient::setLobbies()
{
    std::string message = _receiveMessage.data();
    int nbLobbies = std::atoi(message.substr(0, message.find(" ")).c_str());
    std::string lobbyName;
    int nbClients;
    int level;
    int maxPlace;

    //std::cout << "nbLobbies = " << nbLobbies << std::endl;
    message.erase(0, message.find(" ") + 1);
    //std::cout << "message = " << message << std::endl;
    _lobbies.clear();
    for (int it = 0; it < nbLobbies; it++) {
        lobbyName = message.substr(0, message.find(" "));
        message.erase(0, message.find(" ") + 1);
        nbClients = std::atoi(message.substr(0, message.find(" ")).c_str());
        message.erase(0, message.find(" ") + 1);
        level = std::atoi(message.substr(0, message.find(" ")).c_str());
        message.erase(0, message.find(" ") + 1);
        maxPlace = std::atoi(message.substr(0, message.find(" ")).c_str());
        message.erase(0, message.find(" ") + 1);
        //std::cout << "LobbyName = " << lobbyName << ", nbClients = " << nbClients << ", level = " << level << ", maxPlace = " << maxPlace << std::endl;
        _lobbies[lobbyName] = LobbyClient(lobbyName, nbClients, level, maxPlace);
    }
    /* std::cout << "Voici les lobby que j'ai stock: " << std::endl;
    for (std::map<std::string, LobbyClient>::iterator it = _lobbies.begin(); it != _lobbies.end(); it++) {
        std::cout << "- " << it->second.getName() << " " << it->second.getNbClients() << " " << it->second.getLevel() << " " << it->second.getMaxPlace() << std::endl;
    }
    std::cout << std::endl; */
}

void    UdpClient::checkJoin()
{
    std::string message = _receiveMessage.data();
    int nbClients = 0;
    int clientId;
    std::string status;

    if (message != "ERROR") {
        _sendMessage.erase(0, _sendMessage.find("LOBBY JOIN") + 11);
        _sendMessage.erase(_sendMessage.end() - 1);
        std::cout << "lobbyName = " << _sendMessage << std::endl;
        _myLobby = _lobbies.find(_sendMessage)->second;
        _myLobby.addClient(_myId, false);
        nbClients = std::atoi(message.substr(0, message.find(" ")).c_str());
        message.erase(0, message.find(" ") + 1);
        for (int it = 0; it < nbClients; it++) {
            clientId = std::atoi(message.substr(0, message.find(" ")).c_str());
            message.erase(0, message.find(" ") + 1);
            status = message.substr(0, message.find(" "));
            if (status == "READY")
                _myLobby.addClient(clientId, true);
            else
                _myLobby.addClient(clientId, false);
            message.erase(0, message.find(" ") + 1);
        }
    }
}

void    UdpClient::checkCreate()
{
    std::string message = _receiveMessage.data();

    std::cout << "data = " << _receiveMessage.data() << std::endl;
    if (message == "OK") {
        std::string lobbyInfo = _sendMessage.substr(_sendMessage.find("NEW") + 4);
        std::string lobbyName = lobbyInfo.substr(0, lobbyInfo.find(" "));
        std::string lobbyLevel;
        std::string maxPlace;
        
        lobbyLevel = lobbyInfo.substr(lobbyInfo.find(" "));
        std::cout << "lobbyLevel = " << lobbyInfo << std::endl;
        maxPlace = lobbyInfo.substr(lobbyInfo.find(" ") + 3);
        std::cout << "maxPlace = " << maxPlace << std::endl;
        _myLobby = LobbyClient(lobbyName, 1, std::atoi(lobbyLevel.c_str()), std::atoi(maxPlace.c_str()));
        _myLobby.addClient(_myId);
    }
}