/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** master client header
*/

#ifndef MASTERCLIENT_HPP_
	#define MASTERCLIENT_HPP_

	#include <string>
	#include <memory>
	#include "ActorLoader.hpp"
	#include "Screen.hpp"
	#include "Component.hpp"
	#include "UdpClient.hpp"
	#include "ASceneScreen.hpp"
	#include "ChannelScreen.hpp"
	#include "MenuScreen.hpp"


class MasterClient {
public:
	// CTOR && DTOR
	MasterClient(const std::string &path, Engine::Screen &screen,
	UdpClient &udpClient, Engine::GameEngine &gameEngine,
	const std::unordered_map <unsigned int, Engine::ASceneScreen &>
	&sceneScreens);
	~MasterClient() = default;
	// Method
	void			test() noexcept;
	void			gameLoop() noexcept;
	void			goToCreateGame() noexcept;
	void			goToJoinGame() noexcept;
	void			exit() noexcept;
	void			refreshLobby() noexcept;
	void			joinLobby() noexcept;
	void			setNbrPlayers() noexcept;
	void			setGameNbr() noexcept;
	void			validateCreation() noexcept;
	void			back() noexcept;
private:
	void			changeSceneScreen(unsigned int id) noexcept;
	void			pressButton(const Engine::Vector &) noexcept;
	void			displayScreen() noexcept;
	const std::string	&_path;
	Engine::Screen		&_screen;
	UdpClient		&_udpClient;
	Engine::ActorLoader	_actorLoader;
	Engine::GameEngine	_gameEngine;
	std::unordered_map <unsigned int, Engine::Component &>	_components;
	const std::unordered_map <unsigned int, Engine::ASceneScreen &>
								_sceneScreens;
	std::vector<unsigned int>	_sceneScreenIdOrder;
	unsigned int			_currentScreenId = 0;
	unsigned int			_nbrPlayers = 1;
	unsigned int			_gameNbr = 1;
	std::string			_buttonNameClicked = "none";
};

#endif /* !MASTERCLIENT_HPP_ */
