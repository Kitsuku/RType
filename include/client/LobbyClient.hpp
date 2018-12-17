#ifndef LOBBYCLIENT_HPP_
    # define LOBBYCLIENT_HPP_

    #include <string>
    #include <vector>
    #include "ClientInLobby.hpp"

    class LobbyClient {
        public:;
        LobbyClient(std::string, int, int, int);
        LobbyClient();

        std::string getName() const;
        int getNbClients() const;
        int getLevel() const;
        int getMaxPlace() const;
        void    changeClientStatus(int);
        void    addClient(int);
        void    addClient(int, bool);
        std::vector<ClientInLobby>  getClients() const;

        private:
        std::string _name;
        int _level;
        int _clientsNb;
        int _maxPlace;
        std::vector<ClientInLobby>    _clients;
    };
#endif