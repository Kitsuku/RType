//
// EPITECH PROJECT, 2018
// rtype
// File description:
// pre component
//

#ifndef PRECOMPONENT_HPP_
	#define PRECOMPONENT_HPP_

	#include <memory>
	
namespace Engine {
	struct PreComponent;
}

	#include "IBrain.hpp"
	#include "Rect.hpp"

namespace Engine {
	struct PreComponent {
		IBrain		*brain;
		std::string	path;
		Rect		rectangle;
		bool		colliding = true;
		PreComponent	*bullet = nullptr;
	};
}

#endif /* !PRECOMPONENT_HPP_ */
