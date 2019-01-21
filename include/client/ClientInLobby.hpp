//
// EPITECH PROJECT, 2019
// RType
// File description:
// ClientInLobby class declaration
//

#ifndef CLIENT_IN_LOBBY_HPP_
    # define CLIENT_IN_LOBBY_HPP_

    class ClientInLobby {
    public:
    ClientInLobby();
    ClientInLobby(int, bool);
    ClientInLobby(int);

    int getId() const;
    bool    isReady() const;
    void    setReady(bool);
    void    changeStatus();

    private:
    int     _id;
    bool    _ready;
    };
#endif
