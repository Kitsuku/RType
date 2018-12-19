/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Button header for button present in scene
*/

#ifndef BUTTON_HPP_
	#define BUTTON_HPP_

namespace Engine {
	class Button;
}
	#include "Rect.hpp"
	#include "GameEngine.hpp"
	#include "Vector.hpp"
	#include "ButtonRequest.hpp"

	using fptrButton = void (MasterClient::*) (void);

namespace Engine {
	class Button {
	public:
		// CTOR && DTOR
		Button(const Rect &buttonPosition,
		const ButtonRequest &request);
		~Button() = default;
		// Getter
		const ButtonRequest &getRequest() const noexcept;
		// Method
		bool	isPressed(const Vector &clickPos) const noexcept;
	private:
		const Rect		_buttonPosition;
		const ButtonRequest	_request;
	};
}

#endif /* !BUTTON_HPP_ */
