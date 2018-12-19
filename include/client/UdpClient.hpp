#ifndef UDPCLIENT_HPP_
    # define UDPCLIENT_HPP_

    #include <boost/asio.hpp>
    #include <array>
    #include "LobbyClient.hpp"

    using boost::asio::ip::udp;
    using boost::asio::deadline_timer;

    class UdpClient {
    public:
    UdpClient(std::string, std::string, boost::asio::io_service &);
    void    start(udp::resolver::iterator);
    const LobbyClient   &getLobbyClient() const noexcept;
    std::map<std::string, LobbyClient>      &getLobbies() noexcept;
    void    setLobbies();
    void    setSendMessage(const std::string mesage) noexcept;

    private:
    void    startConnect(udp::resolver::iterator);
    void    startWrite();
    void    startRead();
    void    defineAction();
    void    handleReceive(const boost::system::error_code &, size_t);
    void    manageReceiveMessage();
    void    manageMyLobby();
    void    getMyId();
    void    makeClientReadWrite() noexcept;

    void    checkJoin();
    void    checkCreate();

    udp::endpoint   _myEndpoint;
    udp::endpoint   _serverEndpoint;
    std::string     _sendMessage;
    std::array<char, 1000>     _receiveMessage;
    udp::socket     _socket;
    std::map<std::string, LobbyClient>    _lobbies;
    LobbyClient _myLobby;
    std::string _host;
    boost::asio::io_service &_io;
    int     _myId;
    bool    _inLobby;
    bool    _ready;
    bool    _inGame;
    bool    _firstMessage = true;
    bool    _isReading = false;
    bool    _isConnected = true;
    };
#endif