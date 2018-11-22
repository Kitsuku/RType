//
// EPITECH PROJECT, 2018 
// CPP_rtype_2018
// File description:
// Transform
//

#include "Transform.hpp"

using Engine::Transform;

// Ctor & Dtor
Transform::Transform()
{
}

Transform::Transform(const Engine::Vector &pos, const Engine::Vector &rota,
const Engine::Vector &scale)
: _position(pos), _rotation(rota), _scale(scale)
{
}

Transform::~Transform()
{
}

// Operatpr
// Setter
// Getter
const Engine::Vector	&Transform::getPosition() const noexcept
{
	return _position;
}

const Engine::Vector	&Transform::getRotation() const noexcept
{
	return _rotation;
}

const Engine::Vector	&Transform::getScale() const noexcept
{
	return _scale;
}

// Method
void	Transform::move(const Engine::Vector &translation) noexcept
{
	_position += translation;
}

void	Transform::rotate(const Engine::Vector &rotation) noexcept
{
	_rotation += rotation;
}