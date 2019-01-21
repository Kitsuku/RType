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
#include "msleep.h"
#include <string>

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
	char			inputKey = '0';
	Engine::Vector		clickpos = _screen.getClickPos();
	Engine::GameEngine	gameEngine;
	InputKey		key = _screen.getInputKey();
	Engine::Component	component(gameEngine, true);
	Engine::Component	component_2(gameEngine, true);
	Engine::Transform	transform({200, 200}, {0, 0}, {2, 2});
	Engine::Transform	transform_2({400, 400}, {0, 0}, {2, 2});

	Rect spriteRect = {0, 0, 33, 33};
	Engine::Vector vectorMove(33, 0);
	unsigned int repetition = 2;

	component.getTransform() = transform;
	component_2.getTransform() = transform_2;
	Engine::ARenderer *renderer = _screen.createRenderer("r-typesheet7.gif");
	Engine::ARenderer *renderer_2 = _screen.createRenderer("r-typesheet7.gif");
	

	renderer->show();
	renderer->setOpacity(255);
	renderer->setVectorMove(vectorMove);
	renderer->setMaxRepetition(repetition);
	renderer->setSpriteRect(spriteRect);
	component.setARenderer(renderer);

	renderer_2->show();
	renderer_2->setOpacity(255);
	renderer_2->setVectorMove(vectorMove);
	renderer_2->setMaxRepetition(repetition);
	renderer_2->setSpriteRect(spriteRect);
	component_2.setARenderer(renderer_2);

	/* _components.insert({0, component});
	_components.insert({1, component_2}); */


	while (_screen.isWindowOpen()) {
		_screen.eventHandler();
		clickpos = _screen.getClickPos();
		inputKey = _screen.getControllerKey();
		if (inputKey != '0') {
			_udpClient.setSendMessage(std::to_string(inputKey));
			msleep(0.3);
			_udpClient.setSendMessage("");
		}
		// faire un set message(inputKey);
		key = _screen.getInputKey();
		displayCreateLobbyName(key);
		if (clickpos.getX() != 0 && clickpos.getY() != 0) {
			std::cout << "x : " << clickpos.getX() << " and y : "
			<< clickpos.getY() << std::endl;
		}
		pressButton(clickpos);
		++_refreshTimer;
		if (!_inGame) {
			refreshInGame();
		} else {
			_screen.displayGame(_components);
			_screen.refreshWindow();
			//displayGame();
		}
	}
}

void	MasterClient::goToCreateGame() noexcept
{
	_lobbyName = "";
	_nbrPlayers = 0;
	_gameNbr = 0;
	changeSceneScreen(3);
	std::cout << "createGame" << std::endl;
}

void	MasterClient::goToJoinGame() noexcept
{
	changeSceneScreen(2);
	refreshLobby();
	_selectedLobbyName = "";
	std::cout << "joinGame" << std::endl;
}

void	MasterClient::exit() noexcept
{
	std::cout << "exit" << std::endl;
	_screen.closeWindow();
}

void	MasterClient::refreshLobby() noexcept
{
	_udpClient.setSendMessage("LOBBY INFO");
	msleep(1);
	_udpClient.setSendMessage("");
	displayScreen();
	_screen.addLobbyButtons(_udpClient.getLobbies());
	_refreshTimer = 0;
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

void	MasterClient::play() noexcept
{
	std::vector <ClientInLobby> toto = _udpClient.getLobbyClient().getClients();
	int i = 0;
	for (auto it = toto.begin(); it != toto.end(); it++) {
		std::cout << "before Ready " << i << " : " << it->isReady() << std::endl;
		i++;
	}
	//std::cout << "before Ready " << _udpClient.getReady() << std::endl;
	_udpClient.setSendMessage("LOBBY READY");
	msleep(1);
	_udpClient.setSendMessage("");
	i = 0;
	for (auto it = toto.begin(); it != toto.end(); it++) {
		std::cout << "after Ready " << i << " : " << it->isReady() << std::endl;
		i++;
	}
	std::cout << "after Ready " << _udpClient.getReady() << std::endl;
}

void	MasterClient::joinLobby() noexcept
{
	if (_selectedLobbyName.size() > 0) {
		_udpClient.setSendMessage("LOBBY JOIN " + _selectedLobbyName);
		msleep(1);
		_udpClient.setSendMessage("");
		if (_udpClient.getInLobby()) {
			_playerNbr =
			_udpClient.getLobbyClient().getNbClients() + 1;
			changeSceneScreen(4);
		}
	}
}

void	MasterClient::selectLobby() noexcept
{
	std::cout << "_buttonName : " << _buttonNameClicked << std::endl;
	_selectedLobbyName = _buttonNameClicked;
	displaySelectJoinLobby();
}

void	MasterClient::setNbrPlayers() noexcept
{
	_nbrPlayers = std::stoi(_buttonNameClicked);
	std::cout << "_nbrPlayers : " << _nbrPlayers << std::endl;
	displaySelectionCreateLobby();
}

void	MasterClient::setGameNbr() noexcept
{
	_gameNbr = std::stoi(_buttonNameClicked);
	std::cout << "_gameNbr : " << _gameNbr << std::endl;
	displaySelectionCreateLobby();
}

void	MasterClient::validateCreation() noexcept
{
	// call to serv
	if (_gameNbr != 0 && _nbrPlayers != 0 && _lobbyName.size() != 0) {
		_udpClient.setSendMessage("LOBBY NEW " + _lobbyName + " " +
		std::to_string(_gameNbr) + " " + std::to_string(_nbrPlayers));
		msleep(1);
		_udpClient.setSendMessage("");
		if (_udpClient.getInLobby()) {
			_playerNbr = 1;
			_selectedLobbyName = _lobbyName;
			changeSceneScreen(4);
		} else {
			std::cerr << "Didn't work sorry bro" << std::endl;
		}
	}
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
	ButtonRequest buttonRequest = {"none", nullptr, false, 0};

	if (_screen.isButtonPressed(clickpos)) {
		buttonRequest = _screen.getButtonRequest();
		_buttonNameClicked = buttonRequest.buttonName;
		_nbrJoinLobbyButton = buttonRequest.nbrButton;
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
	} else if (_currentScreenId == 4) {
		drawLobby();
/* 		_screen.drawText(_selectedLobbyName,
		Engine::Vector(260, 245), 35); */
	}
	_screen.refreshWindow();
}

void		MasterClient::displayCreateLobbyName(const InputKey &key)
		noexcept
{
	if (_currentScreenId == 3 && key.textEntered) {
		if (key.value == '\b' && _lobbyName.length() > 0) {
			_lobbyName.pop_back();
		} else if (key.value != '\b' && _lobbyName.length() < 23) {
			_lobbyName += key.value;
		}
		displaySelectionCreateLobby();
	}
}

void		MasterClient::displaySelectionCreateLobby() noexcept
{
	_screen.displaySceneScreen();
	_screen.drawText(_lobbyName, Engine::Vector(260, 245), 35);
	if (_nbrPlayers != 0) {
		_screen.drawRect({390 + 300 * (_nbrPlayers - 1),
		390, 233, 230}, {0, 0, 0, 100});
	}
	if (_gameNbr != 0) {
		_screen.drawRect({290 + 380 * (_gameNbr - 1), 715, 347, 230},
		{0, 0, 0, 100});
	}
	_screen.refreshWindow();
}

void		MasterClient::displaySelectJoinLobby() noexcept
{
	unsigned int		pos_y = _nbrJoinLobbyButton -
				_screen.getInitialNbrButtons() - 1;
	_screen.displaySceneScreen();
	_screen.displayLobbiesPlayer(_udpClient.getLobbies());
	_screen.drawRect({765, 220 + 80 * pos_y, 920, 80},
	{0, 0, 0, 100});
	_screen.refreshWindow();
}

void		MasterClient::drawLobby() noexcept
{
	_screen.drawText(_selectedLobbyName, Engine::Vector(260, 245), 35);
	_screen.drawRect({390 + 300 * (_playerNbr - 1), 390, 220, 420}, {0, 0, 0, 100});
	/* _screen.drawCircle(Engine::Vector(565, 765), {0, 255, 0, 255}, 21);
	_screen.drawCircle(Engine::Vector(865, 765), {0, 255, 0, 255}, 21); */
	int i = 0;
	for (i = 0; i < _udpClient.getLobbyClient().getNbClients(); i++) {
		if (i == 1) {
			_screen.drawCircle(Engine::Vector(565 + 300 * i, 765), {0, 255, 0, 255}, 21);
		} else {
			_screen.drawCircle(Engine::Vector(565 + 300 * i, 765), {0, 0, 255, 255}, 21);
		}
	}
	for (i = i; i < _udpClient.getLobbyClient().getMaxPlace(); i++) {
		_screen.drawCircle(Engine::Vector(565 + 300 * i, 765), {255, 0, 0, 255}, 21);
	}
	for (i = i; i < 4; i++) {
		_screen.drawCircle(Engine::Vector(565 + 300 * i, 765), {0, 0, 0, 255}, 21);
	}
/* 	_screen.drawText(_selectedLobbyName, Engine::Vector(260, 245), 35);
	_screen.drawRect({690, 390, 220, 420}, {0, 0, 0, 100}); */
/* 	_udpClient.getLobbyClient().getName(),
		_udpClient.getLobbyClient().getMaxPlace(), _playerNbr */
}

void		MasterClient::refreshInGame() noexcept
{
	if (_udpClient.getInGame()) {
		_inGame = true;
		changeSceneScreen(_udpClient.getLobbyClient().getLevel() + 4);
	}
}