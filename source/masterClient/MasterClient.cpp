/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Master client member function launching the game
*/

#include "MasterClient.hpp"
#include "SfmlDisplay.hpp"
#include "SfmlController.hpp"
#include "ChannelScreen.hpp"
#include "MenuScreen.hpp"

// CTOR && DTOR
MasterClient::MasterClient(const std::string &path, Engine::Screen &screen,
UdpClient &udpClient, Engine::GameEngine &gameEngine,
const std::unordered_map <unsigned int, Engine::ASceneScreen &> &sceneScreens):
_path(path), _screen(screen), _udpClient(udpClient),
_sceneScreens(sceneScreens)
{
	changeSceneScreen(1);
}
#include <iostream>
void	MasterClient::test() noexcept
{
	std::cout << "success call to masterClient Test" << std::endl;
}

void	MasterClient::gameLoop() noexcept
{
	int				it = 0;
	char			inputKey = '0';
	Engine::Vector		clickpos = _screen.getClickPos();
	Engine::GameEngine	gameEngine;
	InputKey		key = _screen.getInputKey();

	while (_screen.isWindowOpen()) {
/* 		if (_currentScreenId == 4) {
			displayGame()
		} */
		_screen.eventHandler();
		clickpos = _screen.getClickPos();
		inputKey = _screen.getControllerKey();
		key = _screen.getInputKey();
		if (clickpos.getX() != 0 && clickpos.getY() != 0) {
			std::cout << "x : " << clickpos.getX() << " and y : "
			<< clickpos.getY() << std::endl;
		}
		pressButton(clickpos);
	}
}

void	MasterClient::goToCreateGame() noexcept
{
	changeSceneScreen(3);
	std::cout << "createGame" << std::endl;
}

void	MasterClient::goToJoinGame() noexcept
{
	changeSceneScreen(2);
	refreshLobby();
	std::cout << "joinGame" << std::endl;
}

void	MasterClient::exit() noexcept
{
	std::cout << "exit" << std::endl;
	_screen.closeWindow();
}

void	MasterClient::refreshLobby() noexcept
{
	std::cout << "refresh" << std::endl;
	_udpClient.setSendMessage("LOBBY INFO");
	sleep(1);
	_udpClient.setSendMessage("");
	displayScreen();
}

void	MasterClient::back() noexcept
{
	unsigned int	size = _sceneScreenIdOrder.size();

	if (size > 0) {
		changeSceneScreen(size - 1);
		_sceneScreenIdOrder.pop_back();
		_sceneScreenIdOrder.pop_back();
	}
}

void	MasterClient::joinLobby() noexcept
{
	std::cout << "joinLobby" << std::endl;
}

void	MasterClient::setNbrPlayers() noexcept
{
	_nbrPlayers = std::stoi(_buttonNameClicked);
	std::cout << "_nbrPlayers : " << _nbrPlayers << std::endl;
}

void	MasterClient::setGameNbr() noexcept
{
	_gameNbr = std::stoi(_buttonNameClicked);
	std::cout << "_gameNbr : " << _gameNbr << std::endl;
}

void	MasterClient::validateCreation() noexcept
{
	std::cout << "validate Creation" << std::endl;
}

// Private
void		MasterClient::changeSceneScreen(unsigned int id) noexcept
{
	std::unordered_map<unsigned int,
	Engine::ASceneScreen &>::const_iterator it = _sceneScreens.find(id);

	if (it != _sceneScreens.end()) {
		_sceneScreenIdOrder.push_back(id);
		_currentScreenId = it->first;
		_screen.setSceneScreen(it->second);
	}
	if (id != 2) {
		displayScreen();
	}
}

void		MasterClient::pressButton(const Engine::Vector &clickpos)
		noexcept
{
	ButtonRequest buttonRequest = {"none", nullptr, false};

	if (_screen.isButtonPressed(clickpos)) {
		buttonRequest = _screen.getButtonRequest();
		_buttonNameClicked = buttonRequest.buttonName;
		if (buttonRequest.needRequest) {
			(this->*buttonRequest.fptr)();
		} else {
			(this->*buttonRequest.fptr)();
		}
	}
}

void		MasterClient::displayScreen() noexcept
{
	_screen.displaySceneScreen();
	if (_currentScreenId == 2) {
		_screen.displayLobbiesPlayer(_udpClient.getLobbies());
	}
	_screen.refreshWindow();
}