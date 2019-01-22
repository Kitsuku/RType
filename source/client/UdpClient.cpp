/*
** EPITECH PROJECT, 2019
** RType
** File description:
** UdpClient methods
*/

#include <iostream>
#include <fstream>
#include <exception>
#include <boost/throw_exception.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>

#include "UdpClient.hpp"
#include "LobbyClient.hpp"
#include "msleep.h"

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

bool    UdpClient::getInLobby() noexcept
{
    return _inLobby;
}

bool    UdpClient::getInGame() noexcept
{
    return _inGame;
}

bool    UdpClient::getReady() noexcept
{
    return _ready;
}

void    UdpClient::start(udp::resolver::iterator endpointIt)
{
    if (_socket.is_open() == false) {
        _socket.open(udp::v4());
        _socket.non_blocking(true);
        _socket.native_non_blocking(true);
    }
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
                std::cout << "serverEndpoint = " << _serverEndpoint << std::endl;
                if (_inGame == true) {
                    std::string message = std::to_string(_myId) + "\n";
                    _socket.send_to(boost::asio::buffer(message), _serverEndpoint);
                }
                else {
                    _sendMessage = "NOUVEAU CLIENT";
                    _socket.send_to(boost::asio::buffer(_sendMessage), _serverEndpoint);
                }
                makeClientReadWrite();
            }
        });
    }
}

void    UdpClient::makeClientReadWrite() noexcept
{
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
        msleep(1);
    }
    if (_isConnected == false)
        return;
    while (_sendMessage.empty() == true)
        msleep(10);
    if (_sendMessage != "") {
        if (_sendMessage.find("\n") == std::string::npos) {
            _sendMessage += "\n";
        }
        try {
            _socket.send_to(boost::asio::buffer(_sendMessage), _serverEndpoint);
            if (_inGame == true) {
                _socket.send_to(boost::asio::buffer("0\n"), _serverEndpoint);
                _sendMessage.clear();
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    if (_inGame != true)
        msleep(3);
    _sendMessage = "";
    startWrite();
}

void    UdpClient::startRead()
{
    _socket.async_receive_from(boost::asio::buffer(_receiveMessage), _serverEndpoint,
    boost::bind(&UdpClient::handleReceive, this, boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
}

void    UdpClient::handleReceive(const boost::system::error_code& error, size_t bytes_transferred) {
    if (error) {
        std::cout << "Receive failed: " << error.message() << std::endl;
        _isConnected = false;
        return;
    }
    _receiveMessage.at(bytes_transferred - 1) = 0;
    std::string temp = _receiveMessage.data();

    if (temp.find("GAME START") != temp.npos) {
        msleep(1);
    }
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
        //_socket.close();
        _inGame = true;
        udp::resolver resolver(_io);
        _socket = udp::socket(_io);
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
    else if (message == "READY") {
        _myLobby.changeClientStatus(clientId);
        _ready = true;
    }
    std::vector<ClientInLobby>  clients = _myLobby.getClients();
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

    message.erase(0, message.find(" ") + 1);
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
        _lobbies[lobbyName] = LobbyClient(lobbyName, nbClients, level, maxPlace);
    }
}

void    UdpClient::checkJoin()
{
    std::string message = _receiveMessage.data();
    int nbClients = 0;
    int clientId;
    std::string status;

    if (message != "ERROR") {
        _inLobby = true;
        _sendMessage.erase(0, _sendMessage.find("LOBBY JOIN") + 11);
        _sendMessage.erase(std::remove(_sendMessage.begin(),
        _sendMessage.end(), '\n'), _sendMessage.end());
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

    if (message == "OK") {
        std::string lobbyInfo = _sendMessage.substr(_sendMessage.find("NEW") + 4);
        std::string lobbyName = lobbyInfo.substr(0, lobbyInfo.find(" "));
        std::string lobbyLevel;
        std::string maxPlace;
        
        lobbyLevel = lobbyInfo.substr(lobbyInfo.find(" "));
        maxPlace = lobbyInfo.substr(lobbyInfo.find(" ") + 3);
        _myLobby = LobbyClient(lobbyName, 1, std::atoi(lobbyLevel.c_str()), std::atoi(maxPlace.c_str()));
        _myLobby.addClient(_myId);
        _inLobby = true;
    }
}
