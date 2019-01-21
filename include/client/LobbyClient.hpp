//
// EPITECH PROJECT, 2019
// RType
// File description:
// LobbyClient class declaration
//

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
        const LobbyClient	&operator=(const LobbyClient
					    &LobbyClient) noexcept;
        private:
        std::string _name;
        int _clientsNb;
        int _level;
        int _maxPlace;
        std::vector<ClientInLobby>    _clients;
    };
#endif
