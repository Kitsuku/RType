#ifndef CLIENTMANAGER_HPP_
    # define CLIENTMANAGER_HPP_

    #include <array>
    #include "UdpServer.hpp"

    class ClientManager {
    public:

    using ManagerFuncPtr = void    (ClientManager::*)();

    ClientManager(UdpServer *, std::size_t &);

    boost::asio::ip::udp::endpoint  getEndpoint();

    private:
    void    initPtr();
    void    addClient();
    void    manageLobbies();
    bool    isLobbyCommand();
    bool    isNameTaken(std::string);
    int     clientsInLobby(std::string);
    bool    isClientInLobby();
    Lobby   getClientLobby();
    void    sendMessageInLobby(std::string);
    void    getClientsInLobbyInformations(std::string &);

    // Ptr functions
    void    lobbiesInfo();
    void    createLobby();
    void    joinLobby();
    void    setStart();

    UdpServer *_udpServer;
    std::size_t _bytesTransferred;
    std::string _clientMessage;
    boost::asio::ip::udp::endpoint  _clientEndpoint;
    std::array<std::string, 4> _lobbyCommands;
    std::array<ManagerFuncPtr, 4>  _lobbyFunctions;
    };

#endif