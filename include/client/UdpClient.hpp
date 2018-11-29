#ifndef UDPCLIENT_HPP_
    # define UDPCLIENT_HPP_

    #include <boost/asio.hpp>

    using boost::asio::ip::udp;

    class UdpClient {
    public:
    UdpClient(std::string, boost::asio::io_service &);

    private:
    udp::endpoint   _myEndpoint;
    udp::endpoint   _serverEndpoint;
    std::string     _sendMessage;
    std::string     _receiveMessage;
    };
#endif