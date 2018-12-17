/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Screen method calling the displayer
*/

#include <iostream>
#include "Screen.hpp"
#include "DisplayException.hpp"

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
	_displayer.display();
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