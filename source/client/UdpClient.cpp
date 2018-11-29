#include <iostream>
#include "UdpClient.hpp"

using boost::asio::ip::udp;

UdpClient::UdpClient(std::string host, boost::asio::io_service &io)
{
    std::cout << host << std::endl;
    try {
        udp::resolver   resolver(io);
        udp::resolver::query    query(udp::v4(), host, "daytime");
        std::size_t messageLen;
        udp::socket mySocket(io);
        
        std::cout << "début" << std::endl;
        _serverEndpoint = *resolver.resolve(query);
        mySocket.open(udp::v4());
        _sendMessage = "LOBBY INFO\n";
        mySocket.send_to(boost::asio::buffer(_sendMessage), _serverEndpoint);
        messageLen = mySocket.receive_from(boost::asio::buffer(_receiveMessage), _myEndpoint);
        std::cout << "Le serveur m'a envoyé :" << _receiveMessage << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}