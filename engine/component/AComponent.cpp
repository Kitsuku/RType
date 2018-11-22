//
// EPITECH PROJECT, 2018
// rtype
// File description:
// IComponent
//

#include "AComponent.hpp"

using Engine::AComponent;

// Ctor & Dtor
AComponent::AComponent(Engine::GameEngine &gameEngine)
: _gameEngine(gameEngine)
{
}
// Operator
// Setter
// Getter
Engine::Transform	&AComponent::getTransform() noexcept
{
	return _transform;
}

// Method