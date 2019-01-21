/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** structure holding what the button must return
*/

#ifndef BUTTONREQUEST_HPP_
	#define BUTTONREQUEST_HPP_
	
class MasterClient;
	using fptrButton = void (MasterClient::*) (void);

struct ButtonRequest {
	std::string		buttonName;
	fptrButton		fptr;
	bool			needRequest;
	unsigned int		nbrButton;
};

using ButtonRequest = struct ButtonRequest;

#endif /* !BUTTONREQUEST_HPP_ */
