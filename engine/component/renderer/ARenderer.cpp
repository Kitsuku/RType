//
// EPITECH PROJECT, 2018
// rtype
// File description:
// arenderer
//

#include "ARenderer.hpp"

using Engine::ARenderer;

ARenderer::ARenderer(const std::string &texturePath,
	const Rect &spriteRectangle, const Engine::Vector &vectorMove,
	const unsigned int maxRepetition):
	_texturePath(texturePath), _spriteRectangle(spriteRectangle),
	_vectorMove(vectorMove), _maxRepetition(maxRepetition)
{
}

// Getter
bool	ARenderer::isVisible() const noexcept
{
	return _visible;
}

float	ARenderer::getOpacity() const noexcept
{
	return _opacity;
}

bool	ARenderer::isHighLight() const  noexcept
{
	return _highLighted;
}

const std::string	&ARenderer::getTexturePath() const noexcept
{
	return _texturePath;
}

const Rect	&ARenderer::getSpriteRectangle() const noexcept
{
	return _spriteRectangle;
}

unsigned int	ARenderer::getMaxRepetition() const noexcept
{
	return _maxRepetition;
}

const Engine::Vector	&ARenderer::getVectorMove() const noexcept
{
	return _vectorMove;
}


// Setter
void	ARenderer::setOpacity(float opacity) noexcept
{
	_opacity = opacity;
	updateOpacity();
}

void	ARenderer::setHighLight(bool highLighted) noexcept
{
	_highLighted = highLighted;
}

void		ARenderer::setMaxRepetition(const unsigned int maxRepetition)
		noexcept
{
	_maxRepetition = maxRepetition;
}

void		ARenderer::setVectorMove(const Engine::Vector &vectorMove)
		noexcept
{
	_vectorMove = vectorMove;
}

// Method
void	ARenderer::show() noexcept
{
	_visible = true;
}

void	ARenderer::hide() noexcept
{
	_visible = false;
}