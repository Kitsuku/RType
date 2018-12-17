
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

/*int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_service io_service;

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), argv[1], "daytime");
    udp::endpoint receiver_endpoint = *resolver.resolve(query);

    udp::socket socket(io_service);
    socket.open(udp::v4());

    boost::array<char, 1> send_buf  = { 0 };
    socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

    boost::array<char, 128> recv_buf;
    udp::endpoint sender_endpoint;
    size_t len = socket.receive_from(
        boost::asio::buffer(recv_buf), sender_endpoint);

    std::cout.write(recv_buf.data(), len);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}*/

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
