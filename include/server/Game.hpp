#ifndef GAME_HPP_
    # define GAME_HPP_

    #include <boost/asio.hpp>
    #include <vector>
    #include <sstream>
    #include "GameEngine.hpp"
    #include "Client.hpp"

    using boost::asio::ip::udp;

    class Game {
    public:
    Game(Game&&) = default;
    Game(std::vector<Client>, int);
    int getLevel() const;
    std::vector<Client> getClients() const;
    void    setClientNewEndpoint(udp::endpoint, Client) noexcept;
    void    launchGame(std::string) noexcept;
    void    translate(std::ostringstream &) noexcept;

    private:
    std::vector<Client> _clients;
    int _level;
    Engine::GameEngine  _gameEngine;
    };
#endif