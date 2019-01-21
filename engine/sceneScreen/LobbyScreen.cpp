/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** method function for the channel screen
*/

#include "LobbyScreen.hpp"
#include "MasterClient.hpp"

using Engine::LobbyScreen;

LobbyScreen::LobbyScreen(const Engine::Transform &transform,
const bool scrollable):
ASceneScreen(transform, scrollable)
{
	initButtons();
}

LobbyScreen::LobbyScreen(Engine::ARenderer *renderer,
const Engine::Transform &transform, const bool scrollable):
ASceneScreen(renderer, transform, scrollable)
{
	initButtons();
}

LobbyScreen::~LobbyScreen()
{
}

// Private
void	LobbyScreen::initButtons() noexcept
{
	_buttons.push_back(Engine::Button({1185, 925, 250, 55},
	{"1 player(s)", &MasterClient::exit, true, 0}));
	_buttons.push_back(Engine::Button({1455, 925,  250, 55},
	{"2 player(s)", &MasterClient::play, true, 1}));
	_initialNbrButtons = 2;
}