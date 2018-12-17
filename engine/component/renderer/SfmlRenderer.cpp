/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Sfmlrenderer method
*/

#include "SfmlRenderer.hpp"

using Engine::SfmlRenderer;

// Ctor & Dtor
SfmlRenderer::SfmlRenderer(const std::string &path):
ARenderer(path)
{
	setTexturePath(path);
	updateOpacity();
}

SfmlRenderer::SfmlRenderer(const std::string &path,
const Rect &spriteRectangle):
ARenderer(path, spriteRectangle)
{
	setTexturePath(path);
	setSpriteRect(spriteRectangle);
	updateOpacity();
}

SfmlRenderer::SfmlRenderer(const std::string &path,
const Rect &spriteRectangle, const Engine::Vector &vectorMove):
ARenderer(path, spriteRectangle, vectorMove)
{
	setTexturePath(path);
	setSpriteRect(spriteRectangle);
	updateOpacity();
}

SfmlRenderer::SfmlRenderer(const std::string &path,
const Rect &spriteRectangle, const Engine::Vector &vectorMove,
const unsigned int repetition):
ARenderer(path, spriteRectangle, vectorMove, repetition)
{
	setTexturePath(path);
	setSpriteRect(spriteRectangle);
	updateOpacity();
}

// Getter
const sf::Texture	&SfmlRenderer::getTexture() const noexcept
{
	return _texture;
}
const sf::Sprite	&SfmlRenderer::getSprite() const noexcept
{
	return _sprite;
}

// Setter
void	SfmlRenderer::setSpriteRect(const Rect &spriteRectangle) noexcept
{
	_spriteRectangle = spriteRectangle;
	_sprite.setTextureRect(sf::IntRect(_spriteRectangle.pos_x,
	_spriteRectangle.pos_y, _spriteRectangle.width,
	_spriteRectangle.height));
}

void	SfmlRenderer::setTexturePath(const std::string &path) noexcept
{
	_texture.loadFromFile(path);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(_spriteRectangle.pos_x,
	_spriteRectangle.pos_y, _spriteRectangle.width,
	_spriteRectangle.height));
	_texturePath = path;
}

// METHOD
void	SfmlRenderer::setSpritePosition(const Engine::Vector &position)
	noexcept
{
	_sprite.setPosition(position.getX(), position.getY());
}

void	SfmlRenderer::setSpriteRotation(const Engine::Vector &rotation)
	noexcept
{
	_sprite.setRotation(rotation.getX());
}

void	SfmlRenderer::setSpriteScale(const Engine::Vector &scale) noexcept
{
	_sprite.setScale(scale.getX(), scale.getY());
}

void	SfmlRenderer::updateOpacity() noexcept
{
	_sprite.setColor(sf::Color(255, 255, 255, _opacity));
}

void	SfmlRenderer::moveRectSprite() noexcept
{
	sf::IntRect	newRect;

	++_beginRepetition;
	if (_beginRepetition <= _maxRepetition) {
		newRect = sf::IntRect(_spriteRectangle.pos_x +
		_vectorMove.getX() * _beginRepetition,
		_spriteRectangle.pos_y + _vectorMove.getY() *
		_beginRepetition, _spriteRectangle.width,
		_spriteRectangle.height);
	} else {
		_beginRepetition = 0;
		newRect = sf::IntRect(_spriteRectangle.pos_x,
		_spriteRectangle.pos_y,
		_spriteRectangle.width, _spriteRectangle.height);
	}
	_sprite.setTextureRect(newRect);
}