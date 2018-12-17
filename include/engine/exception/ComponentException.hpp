//
// EPITECH PROJECT, 2018
// rtype
// File description:
// component exception
//

#ifndef COMPONENTEXCEPTION_HPP_
	#define COMPONENTEXCEPTION_HPP_

	#include "EngineException.hpp"

namespace Engine {
	class ComponentException : public EngineException {
	public:
		// Ctor & Dtor
		ComponentException(const std::string &msg);
		~ComponentException() override = default;
	};
}

#endif /* !COMPONENTEXCEPTION_HPP_ */
