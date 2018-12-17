/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Header for Controller interface
*/

#ifndef ICONTROLLER_HPP_
	#define ICONTROLLER_HPP_

	#include "InputKey.hpp"

namespace Engine {
	class IController {
	public:
			// Ctor & Dtor
		virtual ~IController() {};
		virtual char convertKey(const InputKey &key) const noexcept = 0;
	};
}

#endif /* !ICONTROLLER_HPP_ */
