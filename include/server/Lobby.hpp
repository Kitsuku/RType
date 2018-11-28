#ifndef LOBBY_HPP_
    # define LOBBY_HPP_

    #include <vector>
    #include "Client.hpp"

    class Lobby {
        public:
        Lobby(std::string, Client, int);
        Lobby();

        std::string getName() const;
        std::vector<Client> getClients() const;
        Client  getMaster() const;
        void    addClient(Client);
        int     getNbClients();
        Client  getClient(int);
        Client  &getClient(boost::asio::ip::udp::endpoint);
        void    setClientReady(boost::asio::ip::udp::endpoint, bool);
        int getLevel() const;

        private:
        std::string _name;
        int _level;
        std::vector<Client> _clientsInLobby;
        Client  _master;
    };

#endif