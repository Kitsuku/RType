/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Exception header for display object
*/

#ifndef DISPLAYEXCEPTION_HPP_
	#define DISPLAYEXCEPTION_HPP_

	#include "EngineException.hpp"

namespace Engine {
	class DisplayException: public EngineException {
	public:
		// Ctor & Dtor
		DisplayException(const std::string &msg);
		~DisplayException() override = default;
	};
}

#endif /* !DISPLAYEXCEPTION_HPP_ */
