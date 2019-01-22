/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Main of rtype client (test)
*/

#include <iostream>
#include <boost/asio.hpp>

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/bind.hpp>
#include <iostream>

#include "UdpClient.hpp"

using boost::asio::ip::udp;

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: ./rtype-client <host> <port>" << std::endl;
        return 84;
    }
    try {
        boost::asio::io_service io;
        udp::resolver resolver(io);
        UdpClient udpClient(av[1], av[2], io);

        udpClient.start(resolver.resolve(udp::resolver::query(udp::v4(), av[1], av[2])));

        io.poll_one();
        io.run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
}
