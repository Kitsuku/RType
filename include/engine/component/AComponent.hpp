//
// EPITECH PROJECT, 2018
// rtype
// File description:
// AComponent
//

#ifndef ACOMPONENT_HPP_
	#define ACOMPONENT_HPP_

	#include "Transform.hpp"
	#include "GameEngine.hpp"

namespace Engine {
	class AComponent {
	public:
		// Ctor & Dtor
		AComponent(GameEngine &gameEngine);
		virtual ~AComponent() = 0;
		// Operator
		// Setter
		// Getter
		Transform	&getTransform() noexcept;
		// Method
		virtual void doTick() throw() = 0;
	protected:
		GameEngine	&_gameEngine;
		Transform	_transform;
	};
}

#endif /* !ACOMPONENT_HPP_ */
