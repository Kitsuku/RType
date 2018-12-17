/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** ASceneScreen method to display screen
*/

#include "ASceneScreen.hpp"

using Engine::ASceneScreen;

// CTOR
ASceneScreen::ASceneScreen(const Engine::Transform &transform,
const bool scrollable): _transform(transform), _scrollable(scrollable)
{
	_initialPos = transform.getPosition();
}

ASceneScreen::ASceneScreen(Engine::ARenderer *renderer,
const Engine::Transform &transform, const bool scrollable):
_renderer(renderer), _transform(transform), _scrollable(scrollable)
{
	_initialPos = transform.getPosition();
}

ASceneScreen::~ASceneScreen()
{
	delete _renderer;
}

// Getter
Engine::ARenderer	*ASceneScreen::getARenderer() const noexcept
{
	return _renderer;
}

bool			ASceneScreen::isScrollable() const noexcept
{
	return _scrollable;
}

const ButtonRequest		&ASceneScreen::getRequest() const noexcept
{
	return _buttons[_buttonPos].getRequest();
}

Engine::Transform	&ASceneScreen::getTransform() noexcept
{
	return _transform;
}

const Engine::Transform	&ASceneScreen::getTransform() const noexcept
{
	return _transform;
}

const Engine::Vector		&ASceneScreen::getInitialPos() const noexcept
{
	return _initialPos;
}

const std::vector<Engine::Button>	&ASceneScreen::getButtons()
					const noexcept
{
	return _buttons;
}

// Setter
void		ASceneScreen::setARenderer(Engine::ARenderer *renderer)
		noexcept
{
	if (_renderer == nullptr) {
		_renderer = renderer;
	} else {
	if (renderer->isVisible()) {
		_renderer->show();
		} else {
			_renderer->hide();
		}
		_renderer->setHighLight(renderer->isHighLight());
		_renderer->setMaxRepetition(renderer->getMaxRepetition());
		_renderer->setOpacity(renderer->getOpacity());
		_renderer->setSpriteRect(renderer->getSpriteRectangle());
		_renderer->setTexturePath(renderer->getTexturePath());
		_renderer->setVectorMove(renderer->getVectorMove());
	}
}

void		ASceneScreen::setScrollabe(const bool scrollable) noexcept
{
	_scrollable = scrollable;
}

void		ASceneScreen::setButtonPos(int buttonPos) noexcept
{
	_buttonPos = buttonPos;
}

void		ASceneScreen::setButtons(std::vector<Engine::Button> buttons)
		noexcept
{
	_buttons.clear();
	for (auto a = buttons.begin(); a != buttons.end(); a++) {
		_buttons.push_back(*a);
	}
}

void		ASceneScreen::setInitialPos(Engine::Vector initialPos)
		noexcept
{
	_initialPos = initialPos;
}

// Method
bool		ASceneScreen::isPressed(const Engine::Vector &clickPos)
		noexcept
{
	std::vector<Engine::Button>::iterator	it = _buttons.begin();
	bool					end = false;

	_buttonPos = 0;
	while (!end && it != _buttons.end()) {
		end = it->isPressed(clickPos);
		++_buttonPos;
		++it;
	}
	if (!end) {
		_buttonPos = 0;
	} else {
		--_buttonPos;
	}
	return end;
}

const ASceneScreen	&ASceneScreen::operator=(const Engine::ASceneScreen
			&sceneScreen) noexcept
{
	this->getTransform() = sceneScreen.getTransform();
	this->setButtonPos(0);
	this->setButtons(sceneScreen.getButtons());
	this->setScrollabe(sceneScreen.isScrollable());
	this->setARenderer(sceneScreen.getARenderer());
	this->setInitialPos(sceneScreen.getInitialPos());

	return *this;
}