/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Header for SfmlController
*/

#ifndef SfmlController_HPP_
	#define SfmlController_HPP_

	#include "IController.hpp"

namespace Engine {
	class SfmlController: public IController {
	public:
		// Ctor & Dtor
		SfmlController();
		~SfmlController() = default;
		// Method
		char convertKey(const InputKey &key) const noexcept;
	private:
		char convertArrowKey(const int keyValue) const noexcept;
	};
}

#endif /* !SfmlController_HPP_ */
