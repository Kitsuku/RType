/*
** EPITECH PROJECT, 2019
** RType
** File description:
** Main of RType server
*/

#include "UdpServer.hpp"

using boost::asio::ip::udp;

int main()
{
  try
  {
    boost::asio::io_service io_service;
  
    UdpServer server(io_service);
    io_service.poll_one();
    //io_service.poll_two();
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
