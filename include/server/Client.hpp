#ifndef CLIENT_HPP_
    # define CLIENT_HPP_

    #include <string>
    #include <thread>
    #include <boost/asio.hpp>

    class Client {
        public:
            Client();
            Client(std::string, unsigned short, boost::asio::ip::udp::endpoint);

            const std::string getAddress() const;
            const unsigned short  getPort() const;
            
            void    setMessage(std::string);
            const std::string getMessage() const;
            boost::asio::ip::udp::endpoint  getEndpoint() const;
            void    setReady(bool);
            bool    getReady() const;
        private:
            std::string _address;
            unsigned short  _port;
            std::string _message;
            boost::asio::ip::udp::endpoint    _endpoint;
            bool    _isReady = false;
    };

#endif