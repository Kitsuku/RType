/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** method function for the lobby screen
*/

#include "MenuScreen.hpp"
#include "MasterClient.hpp"

using Engine::MenuScreen;

MenuScreen::MenuScreen(const Engine::Transform &transform,
const bool scrollable): ASceneScreen(transform, scrollable)
{
	initButtons();
}

MenuScreen::MenuScreen(Engine::ARenderer *renderer,
const Engine::Transform &transform, const bool scrollable):
ASceneScreen(renderer, transform, scrollable)
{
	initButtons();
}

MenuScreen::~MenuScreen()
{
}

// Private
void	MenuScreen::initButtons() noexcept
{
	_buttons.push_back(Engine::Button({692, 485, 520, 95},
	{"joinGame", &MasterClient::goToJoinGame, true, 0}));
	_buttons.push_back(Engine::Button({692, 627, 520, 95},
	{"create", &MasterClient::goToCreateGame, true, 1}));
	_buttons.push_back(Engine::Button({692, 768, 520, 95},
	{"exit", &MasterClient::exit, true, 2}));
	_initialNbrButtons = 3;
}