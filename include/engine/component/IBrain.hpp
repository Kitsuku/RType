//
// EPITECH PROJECT, 2018
// rtype
// File description:
// i brain
//

#ifndef IBRAIN_HPP_
	#define IBRAIN_HPP_

namespace Engine {
	class IBrain;
}

	#include "IComponent.hpp"

namespace Engine {
	class IBrain {
	public:
		// Ctor & Dtor
		IBrain() = default;
		virtual ~IBrain() = 0;
		// Setter
		virtual void	setComponent(IComponent &compo) = 0;
		// Method
		virtual void	doTick() = 0;
	};
}

#endif /* !IBRAIN_HPP_ */
