/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Button method
*/

#include "Button.hpp"

using Engine::Button;

// CTOR
Button::Button(const Rect &buttonPosition, const ButtonRequest &request):
_buttonPosition(buttonPosition), _request(request)
{
}

// Getter
const ButtonRequest	&Button::getRequest() const noexcept
{
	return _request;
}
// Method
bool	Button::isPressed(const Vector &clickPos) const noexcept
{
	const unsigned int posX = static_cast<const unsigned int>
	(clickPos.getX());
	const unsigned int posY = static_cast<const unsigned int>
	(clickPos.getY());
	bool	ret = false;

	if (posX >= _buttonPosition.pos_x &&
	posX <= _buttonPosition.pos_x + _buttonPosition.width &&
	posY >= _buttonPosition.pos_y &&
	posY <= _buttonPosition.pos_y + _buttonPosition.height) {
		ret = true;
	}
	return ret;
}