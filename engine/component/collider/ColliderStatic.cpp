//
// EPITECH PROJECT, 2018
// rtype
// File description:
// collider static
//

#include "ColliderStatic.hpp"

using Engine::ColliderStatic;

// Ctor
ColliderStatic::ColliderStatic(const Engine::Vector &start,
const Engine::Vector &size)
: _origin(start), _end(start)
{
	_end += size;
}

// Getter
const Engine::Vector	ColliderStatic::getEnd() const noexcept
{
	return _end;
}

const Engine::Vector	ColliderStatic::getOrigin() const noexcept
{
	return _origin;
}

// Method
bool	ColliderStatic::isColliding(const Engine::ICollider &collide)
const noexcept
{
	const Vector	origin = collide.getOrigin();
	const Vector	end = collide.getEnd();

	if (origin.getX() <= _end.getX() && _origin.getX() <= end.getX()
	&& origin.getY() <= _end.getY() && _origin.getY() <= end.getY())
		return true;
	return false;
}