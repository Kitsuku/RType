/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** method function for the channel screen
*/

#include "ChannelScreen.hpp"
#include "MasterClient.hpp"

using Engine::ChannelScreen;

ChannelScreen::ChannelScreen(const Engine::Transform &transform,
const bool scrollable): ASceneScreen(transform, scrollable)
{
	initButtons();
}

ChannelScreen::ChannelScreen(Engine::ARenderer *renderer,
const Engine::Transform &transform, const bool scrollable):
ASceneScreen(renderer, transform, scrollable)
{
	initButtons();
}

ChannelScreen::~ChannelScreen()
{
}

// Private
void	ChannelScreen::initButtons() noexcept
{
	_buttons.push_back(Engine::Button({230, 935, 182, 35},
	{"back", &MasterClient::back, true, 0}));
	_buttons.push_back(Engine::Button({530, 935, 192, 38},
	{"joinLobby", &MasterClient::joinLobby, true, 1}));
	_buttons.push_back(Engine::Button({530, 885, 192, 38},
	{"refreshLobby", &MasterClient::refreshLobby, true, 2}));
	_initialNbrButtons = 3;
}
