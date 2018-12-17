/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** 
*/

#include "SfmlController.hpp"

using Engine::SfmlController;

// Ctor & Dtor
SfmlController::SfmlController()
{
}

// Method
char	SfmlController::convertKey(const InputKey &key) const noexcept
{
	char	ret = '0';

	if (key.valid) {
		if (key.textEntered && key.value == ' ') {
			ret = '5';
		} else {
			ret = convertArrowKey(key.value);
		}
	}
	return ret;
}

char	SfmlController::convertArrowKey(const int keyValue) const noexcept
{
	char	ret = '0';

	switch(keyValue) {
		case 71:
			ret = '1';
			break;
		case 72:
			ret = '2';
			break;
		case 73:
			ret = '3';
			break;
		case 74:
			ret = '4';
			break;
	}
	return ret;
}