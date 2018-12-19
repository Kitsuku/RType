#ifndef GAME_HPP_
    # define GAME_HPP_

    #include <boost/asio.hpp>
    #include <vector>
    #include "Client.hpp"

    using boost::asio::ip::udp;

    class Game {
    public:
    Game(std::vector<Client>, int);
    int getLevel() const;

    private:
    std::vector<Client> _clients;
    // stock components ici et créer méthode pour les moves??
    int _level;
    };
#endif