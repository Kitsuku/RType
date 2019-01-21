//
// EPITECH PROJECT, 2018
// rtype
// File description:
// collider
//

#include "Collider.hpp"
#include "ComponentException.hpp"

using Engine::Collider;

// Ctor & Dtor
Collider::Collider(const Engine::IComponent &compo, const Rect &rect)
: _component(compo)
{
	_size.setX(static_cast<float>(rect.width));
	_size.setY(static_cast<float>(rect.height));
}

Collider::Collider(const Engine::IComponent &compo, unsigned int width,
unsigned int height)
: _component(compo)
{
	_size.setX(static_cast<float>(width));
	_size.setY(static_cast<float>(height));
}

// Getter
const Engine::Vector	Collider::getEnd() const noexcept
{
	Engine::Vector	position = _component.getTransform().getPosition();
	Engine::Vector	end;

	end.setX(position.getX() + _size.getX());
	end.setY(position.getY() + _size.getY());
	return end;
}

const Engine::Vector	Collider::getOrigin() const noexcept
{
	return _component.getTransform().getPosition();
}

// Method
bool	Collider::isColliding(const Engine::ICollider &collide)
const noexcept
{
	const Vector	origin = collide.getOrigin();
	const Vector	end = collide.getEnd();
	const Vector	myOrigin = this->getOrigin();
	const Vector	myEnd = this->getEnd();

	if (origin.getX() <= myEnd.getX() && myOrigin.getX() <= end.getX()
	&& origin.getY() <= myEnd.getY() && myOrigin.getY() <= end.getY())
		return true;
	return false;
}

// Static method
Collider	*Collider::wrapRenderer(const Engine::IComponent &target)
{
	Engine::ARenderer	*rend = nullptr;
	Rect			rect;

	rend = target.getARenderer();
	if (rend == nullptr)
		throw Engine::ComponentException("Can't wrap a "
		"null Renderer");
	rect = rend->getSpriteRectangle();
	return new Collider(target, rect);
}
