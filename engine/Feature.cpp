//
// EPITECH PROJECT, 2018
// rtype
// File description:
// feature
//

#include "Feature.hpp"

using Engine::Feature;

// Ctor & Dtor
Feature::Feature(unsigned int life, unsigned int damages)
: _maxLife(life), _life(life), _damages(damages)
{
}

// Setter
void	Feature::setSpeed(float speed) noexcept
{
	_speed = speed;
}

void	Feature::setDamageable(bool state) noexcept
{
	_isDamageable = state;
}

void	Feature::setDamages(unsigned int damages) noexcept
{
	_damages = damages;
}

// Getter
bool		Feature::isAlive() const noexcept
{
	return _alive;
}

bool		Feature::isDeletable() const noexcept
{
	return _isDeletable;
}

float		Feature::getSpeed() const noexcept
{
	return _speed;
}

unsigned int	Feature::getDamages() const noexcept
{
	return _damages;
}

// Method
void	Feature::kill() noexcept
{
	_life = 0;
	_alive = false;
}

void	Feature::resurect() noexcept
{
	_life = _maxLife;
	_alive = true;
}

void	Feature::heal(unsigned int value) noexcept
{
	_life += value;
	if (_life > _maxLife)
		_life = _maxLife;
}

void	Feature::damage(unsigned int value) noexcept
{
	if (!_isDamageable)
		return;
	if (value >= _life) {
		_life = 0;
		_alive = false;
	} else
		_life -= value;
}