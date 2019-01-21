/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Screen method calling the displayer
*/

#include <iostream>
#include "Screen.hpp"
#include "DisplayException.hpp"
#include "MasterClient.hpp"

using Engine::Screen;

// Ctor
Screen::Screen(const Engine::IController &controller,
Engine::IDisplay &displayer,
Engine::ASceneScreen &sceneScreen):
_controller(controller), _displayer(displayer), _sceneScreen(sceneScreen)
{
}

// Getter
const ButtonRequest	&Screen::getButtonRequest() const noexcept
{
	return _request;
}

// Setter
void			Screen::setSceneScreen(const Engine::ASceneScreen
					&sceneScreen) noexcept
{
	_sceneScreen = sceneScreen;
}

// Method
void	Screen::displayGame(std::unordered_map
	<unsigned int, Engine::Component &> &mapComponent) const noexcept
{
	std::unordered_map<unsigned int, Engine::Component &>::iterator it =
	mapComponent.begin();

	try {
		_displayer.drawSceneScreen(_sceneScreen);
	} catch (Engine::DisplayException &error) {
		std::cerr << error.what() << std::endl;
	}
	while (it != mapComponent.end()) {
		try {
			_displayer.drawComponent(it->second);
		} catch (Engine::DisplayException &error) {
			std::cerr << error.what() << std::endl;
		}
		++it;
	}
}

void	Screen::displaySceneScreen() const noexcept
{
	try {
		_displayer.drawSceneScreen(_sceneScreen);
	} catch (Engine::DisplayException &error) {
		std::cerr << error.what() << std::endl;
	}
}

void	Screen::eventHandler() noexcept
{
	_displayer.eventHandler();
	_inputKey = _displayer.getInputKey();
	_clickPos = _displayer.getClickPos();
}

bool	Screen::isWindowOpen() const noexcept
{
	return _displayer.isWindowOpen();
}

const InputKey	&Screen::getInputKey() const noexcept
{
	return _inputKey;
}

const Engine::Vector	&Screen::getClickPos() const noexcept
{
	return _clickPos;
}

char		Screen::getControllerKey() const noexcept
{
	return _controller.convertKey(_inputKey);
}

bool		Screen::isButtonPressed(const Engine::Vector &clickPos) noexcept
{
	const bool	ret = _sceneScreen.isPressed(clickPos);

	_request = _sceneScreen.getRequest();
	return ret;
}

void		Screen::addButton(const Engine::Button &button) noexcept
{
	_sceneScreen.addButton(button);
}

void		Screen::addButton(const Rect &buttonPositon,
		const ButtonRequest &buttonRequest)noexcept
{
	_sceneScreen.addButton(Engine::Button(buttonPositon, buttonRequest));
}

void		Screen::setBackInitialButtons() noexcept
{
	_sceneScreen.setBackInitialButtons();
}

void		Screen::addLobbyButtons(std::map<std::string,
		LobbyClient> &lobbies) noexcept
{
	std::map<std::string, LobbyClient>::iterator	it;
	unsigned int					pos_y = 0;
	unsigned int					nbrInitialButton;

	if (!lobbies.empty()) {
		_sceneScreen.setBackInitialButtons();
		nbrInitialButton = _sceneScreen.getInitialNbrButtons();
		it = lobbies.begin();
		while (it != lobbies.end() && pos_y < 6) {
			_sceneScreen.addButton(
			{775, 230 + pos_y * 80, 900, 60},
			{it->second.getName(), &MasterClient::selectLobby,
			true, nbrInitialButton + pos_y + 1});
			++it;
			++pos_y;
		}
	}
}

void		Screen::setButtons(std::vector<Engine::Button> buttons)
		noexcept
{
	_sceneScreen.setButtons(buttons);
}

unsigned short	Screen::getInitialNbrButtons() const noexcept
{
	return _sceneScreen.getInitialNbrButtons();
}

Engine::ARenderer	*Screen::createRenderer(
			const std::string &ressourcesPath) const noexcept
{
	return _displayer.createRenderer(ressourcesPath);
}

Engine::ARenderer	*Screen::createRenderer(
			const std::string &ressourcesPath,
			const Rect &spriteRectangle) const noexcept
{
	return _displayer.createRenderer(ressourcesPath, spriteRectangle);
}

Engine::ARenderer	*Screen::createRenderer(
			const std::string &ressourcesPath,
			const Rect &spriteRectangle, const Engine::Vector &moveRect)
			const noexcept
{
	return _displayer.createRenderer(ressourcesPath, spriteRectangle,
	moveRect);
}

Engine::ARenderer	*Screen::createRenderer(
			const std::string &ressourcesPath,
			const Rect &spriteRectangle, const Engine::Vector &moveRect,
			const unsigned int maxRepetition) const noexcept
{
	return _displayer.createRenderer(ressourcesPath, spriteRectangle,
	moveRect, maxRepetition);
}

void			Screen::refreshWindow() noexcept
{
	_displayer.display();
}

void		Screen::displayLobbiesPlayer(std::map<std::string,
					LobbyClient> lobbies) noexcept
{
	std::map<std::string, LobbyClient>::iterator	it;
	std::string					text;
	unsigned int					pos_y = 0;

	if (!lobbies.empty()) {
		it = lobbies.begin();
		while (it != lobbies.end() && pos_y < 6) {
			drawLobbyInfo(it->second, pos_y);
			++it;
			++pos_y;
		}
	}
}

void		Screen::closeWindow() noexcept
{
	_displayer.closeWindow();
}

void		Screen::drawLobbyInfo(const LobbyClient &lobby,
		const unsigned int &pos_y) noexcept
{
	std::string	text;

	text = "Level : " + std::to_string(lobby.getLevel());
	_displayer.drawBox({775, 230 + pos_y * 80, 900, 60});
	_displayer.drawText(text,
	Engine::Vector(785, 240 + pos_y * 80), 35);
	text = "Name : " + lobby.getName();
	_displayer.drawText(text,
	Engine::Vector(1100, 240 + pos_y * 80), 35);
	text = std::to_string(lobby.getNbClients()) + "/"
	+ std::to_string(lobby.getMaxPlace());
	_displayer.drawText(text,
	Engine::Vector(1600, 255 + pos_y * 80), 27);
}

void		Screen::drawText(const std::string &text,
		const Engine::Vector &position, unsigned int size) noexcept
{
	_displayer.drawText(text, position, size);
}

void		Screen::drawRect(const Rect &rect, const Color &color) noexcept
{
	_displayer.drawRect(rect, color);
}

void		Screen::drawCircle(const Engine::Vector &position,
		const Color &color, float radius) noexcept
{
	_displayer.drawCircle(position, color, radius);
}