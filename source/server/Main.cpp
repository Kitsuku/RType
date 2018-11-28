#include "UdpServer.hpp"

using boost::asio::ip::udp;

int main()
{
  try
  {
    boost::asio::io_service io_service;
    UdpServer server(io_service);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
