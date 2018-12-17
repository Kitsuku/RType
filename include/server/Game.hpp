#ifndef GAME_HPP_
    # define GAME_HPP_

    #include <boost/asio.hpp>
    #include <vector>
    #include "Client.hpp"
    #include "GameEngine.hpp"

    using boost::asio::ip::udp;

    class Game {
    public:
    Game(std::vector<Client>, int, Engine::GameEngine &);
    int getLevel() const;
    //void    setEngine(Engine::GameEngine);

    private:
    std::vector<Client> _clients;
    Engine::GameEngine  &_engine;
    int _level;
    };
#endif