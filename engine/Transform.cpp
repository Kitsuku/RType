//
// EPITECH PROJECT, 2018 
// CPP_rtype_2018
// File description:
// Transform
//

#include <iomanip>
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

void	Transform::place(const Engine::Vector &position) noexcept
{
	_position = position;
}

// Extern operator
std::ostream	&operator<<(std::ostream &stream,
			const Transform &target) noexcept
{
	stream << std::fixed << std::setprecision(5);
	stream << "Position: " << target.getPosition();
	if (!target.getRotation().isNull())
		stream << " Rotation: " << target.getRotation();
	if (target.getScale() != Engine::Vector(1.0, 1.0))
		stream << " Scale: " << target.getScale();
	stream << std::defaultfloat;
	return stream;
}