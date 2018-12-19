/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** method function for the channel screen
*/

#include "CreateLobbyScreen.hpp"
#include "MasterClient.hpp"

using Engine::CreateLobbyScreen;

CreateLobbyScreen::CreateLobbyScreen(const Engine::Transform &transform, const bool scrollable):
ASceneScreen(transform, scrollable)
{
	initButtons();
}

CreateLobbyScreen::CreateLobbyScreen(Engine::ARenderer *renderer,
const Engine::Transform &transform, const bool scrollable):
ASceneScreen(renderer, transform, scrollable)
{
	initButtons();
}

CreateLobbyScreen::~CreateLobbyScreen()
{
}

// Private
void	CreateLobbyScreen::initButtons() noexcept
{
	_buttons.push_back(Engine::Button({405, 405, 205, 205},
	{"1 player(s)", &MasterClient::setNbrPlayers, true}));
	_buttons.push_back(Engine::Button({705, 405,  205, 205},
	{"2 player(s)", &MasterClient::setNbrPlayers, true}));
	_buttons.push_back(Engine::Button({1005, 405,  205, 205},
	{"3 player(s)", &MasterClient::setNbrPlayers, true}));
	_buttons.push_back(Engine::Button({1305, 405,  205, 205},
	{"4 player(s)", &MasterClient::setNbrPlayers, true}));
	_buttons.push_back(Engine::Button({305, 730,  320, 205},
	{"1 game 1", &MasterClient::setGameNbr, true}));
	_buttons.push_back(Engine::Button({685, 730, 320, 205},
	{"2 game 2", &MasterClient::setGameNbr, true}));
	_buttons.push_back(Engine::Button({1065, 730, 320, 205},
	{"3 game 3", &MasterClient::setGameNbr, true}));
	_buttons.push_back(Engine::Button({1400, 735, 300, 55},
	{"validate", &MasterClient::validateCreation, true}));
	_buttons.push_back(Engine::Button({1400, 865, 300, 65},
	{"back", &MasterClient::back, true}));
}