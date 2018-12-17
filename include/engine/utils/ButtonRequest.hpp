/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** structure holding what the button must return
*/

#ifndef BUTTONREQUEST_HPP_
	#define BUTTONREQUEST_HPP_
	
	#include "GameEngine.hpp"
	using fptrButton = void (Engine::GameEngine::*) (void);

struct ButtonRequest {
	fptrButton	fptr;
	bool		needRequest;
};

using ButtonRequest = struct ButtonRequest;

#endif /* !BUTTONREQUEST_HPP_ */
