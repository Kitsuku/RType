/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** SfmlDisplay objects method for graphicals parts
*/

#include "SfmlDisplay.hpp"
#include "SfmlRenderer.hpp"
#include "DisplayException.hpp"

using Engine::SfmlDisplay;
#include <iostream>
// Ctor & Dtor
SfmlDisplay::SfmlDisplay(std::string &path): _path(path)
{
	_path.replace(_path.find("rtype-client"), std::string::npos,
	"ressources/");
}

SfmlDisplay::~SfmlDisplay()
{
}

// Method
void	SfmlDisplay::createWindow(bool fullscreen, const std::string &name)
	noexcept
{
	if (fullscreen) {
		_window.create(sf::VideoMode::getDesktopMode(), name,
		sf::Style::Fullscreen);
	} else {
		_window.create(sf::VideoMode::getDesktopMode(), name,
		sf::Style::Titlebar | sf::Style::Close);
	}
}

void	SfmlDisplay::createWindow(unsigned int width, unsigned height,
	const std::string &name) noexcept
{
	_window.create(sf::VideoMode(width, height, 64), name,
	sf::Style::Titlebar | sf::Style::Close);
	return;
}

Engine::ARenderer	*SfmlDisplay::createRenderer(const std::string
			&ressourcesPath)
			const noexcept
{
	SfmlRenderer	*renderer = new SfmlRenderer(_path + ressourcesPath);

	return renderer;
}

Engine::ARenderer	*SfmlDisplay::createRenderer(const std::string
			&ressourcesPath, const Rect &spriteRectangle)
			const noexcept
{
	SfmlRenderer	*renderer = new SfmlRenderer(_path + ressourcesPath,
				spriteRectangle);

	return renderer;
}

Engine::ARenderer	*SfmlDisplay::createRenderer(const std::string
			&ressourcesPath, const Rect &spriteRectangle,
			const Engine::Vector &moveRect)
			const noexcept
{
	SfmlRenderer	*renderer = new SfmlRenderer(_path + ressourcesPath,
				spriteRectangle, moveRect);

	return renderer;
}

Engine::ARenderer	*SfmlDisplay::createRenderer(const std::string
			&ressourcesPath, const Rect &spriteRectangle,
			const Engine::Vector &moveRect,
			const unsigned int repetition)
			const noexcept
{
	SfmlRenderer	*renderer = new SfmlRenderer(_path + ressourcesPath,
				spriteRectangle, moveRect, repetition);

	return renderer;
}

void			SfmlDisplay::setFont()
{
	if (!_font.loadFromFile(_path + "Future_n0t_Found_Regular.ttf")) {
		throw DisplayException("No font provided");
	}
	_sfText.setFont(_font);
}

void	SfmlDisplay::drawComponent(const Engine::IComponent &component)
{
	SfmlRenderer *sfmlRenderer =
		dynamic_cast <SfmlRenderer *> (component.getARenderer());

	if (sfmlRenderer == NULL) {
		throw DisplayException("No renderer provided");
	}
	if (sfmlRenderer->isVisible()) {
		createRenderState(component.getTransform());
		sfmlRenderer->moveRectSprite();
		_window.draw(sfmlRenderer->getSprite(), _renderStates);
	}
}

void	SfmlDisplay::drawSceneScreen(Engine::ASceneScreen
				&sceneScreen)
{
	SfmlRenderer *sfmlRenderer = nullptr;

	try {
		sfmlRenderer = dynamic_cast <SfmlRenderer *>
		(sceneScreen.getARenderer());
	} catch (const std::exception& e) {
		throw DisplayException(e.what());
	}
	if (sfmlRenderer == nullptr) {
		throw DisplayException("No renderer provided");
	}
	if (sceneScreen.isScrollable()) {
		scrollable(sceneScreen, sfmlRenderer);
	} else {
		_window.draw(sfmlRenderer->getSprite());
	}
}

const InputKey	&SfmlDisplay::getInputKey() const noexcept
{
	return _inputKey;
}

const Engine::Vector	&SfmlDisplay::getClickPos() const noexcept
{
	return _clickPos;
}

bool		SfmlDisplay::isWindowOpen() const noexcept
{
	return _window.isOpen();
}

void	SfmlDisplay::displayPause() const noexcept
{
	return;
}

void	SfmlDisplay::displayMenu() const noexcept
{
	return;
}

void	SfmlDisplay::displayBackground() const noexcept
{
	return;
}

void	SfmlDisplay::playBackgroundMusic(std::string) const noexcept
{
	return;
}

void	SfmlDisplay::display() noexcept
{
	_window.display();
	_window.clear();
}

void		SfmlDisplay::drawBox(const Rect &box) noexcept
{
	sf::RectangleShape	rectangle;

	rectangle.setSize(sf::Vector2f(box.width, box.height));
	rectangle.setFillColor(sf::Color(255, 255, 255, 123));
	rectangle.setPosition(box.pos_x, box.pos_y);
	_window.draw(rectangle);
}

void		SfmlDisplay::drawText(const std::string &text,
		const Vector &position, unsigned int size) noexcept
{
	_sfText.setString(text);
	_sfText.setCharacterSize(size);
	_sfText.setFillColor(sf::Color::Black);
	_sfText.setPosition(position.getX(), position.getY());
	_window.draw(_sfText);
}

void		SfmlDisplay::closeWindow() noexcept
{
	_window.close();
}

// Private method
void	SfmlDisplay::createRenderState(
			const Engine::Transform &transform)
{
	Engine::Vector	position = transform.getPosition();
	Engine::Vector	rotation = transform.getRotation();
	Engine::Vector	scale = transform.getScale();
	sf::Transform	sfTransform;

	sfTransform.translate(position.getX(), position.getY());
	sfTransform.rotate(rotation.getX());
	sfTransform.scale(scale.getX(), scale.getY());
	_renderStates.transform = sfTransform;
}

void	SfmlDisplay::eventHandler() noexcept
{
	_inputKey = {false, 0, false};
	_clickPos = {0, 0};

	if (_window.pollEvent(_event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			_window.close();
		}
		setInputKey();
		setClickPos();
	}
}

void	SfmlDisplay::setInputKey() noexcept
{
	if (_event.type == sf::Event::Closed) {
		_inputKey.valid = false;
		_inputKey.value = -1;
		_window.close();
	} else if (_event.type == sf::Event::KeyPressed) {
		_inputKey.valid = true;
		_inputKey.value = _event.text.unicode;
	}
	if (_event.type == sf::Event::TextEntered &&
	_event.text.unicode <= 127) {
		_inputKey.valid = true;
		_inputKey.value = _event.text.unicode;
		_inputKey.textEntered = true;
	}
}

void	SfmlDisplay::setClickPos() noexcept
{
	if  (_event.type == sf::Event::MouseButtonReleased) {
		_clickPos = {static_cast<float> (_event.mouseButton.x),
		static_cast<float> (_event.mouseButton.y)};
	}
}

void	SfmlDisplay::scrollable(Engine::ASceneScreen &sceneScreen,
	Engine::SfmlRenderer *sfmlRenderer) noexcept
{
	Engine::Transform	&transform = sceneScreen.getTransform();
	const unsigned int	textureWidth =
				sfmlRenderer->getTexture().getSize().x;

	transform.move(Vector(-0.1, 0));
	if ((-transform.getPosition().getX()) > textureWidth) {
		transform.place(sceneScreen.getInitialPos());
	}
	createRenderState(transform);
	_window.draw(sfmlRenderer->getSprite(), _renderStates);
	_renderStates.transform.translate(textureWidth, 0);
	_window.draw(sfmlRenderer->getSprite(), _renderStates);
}