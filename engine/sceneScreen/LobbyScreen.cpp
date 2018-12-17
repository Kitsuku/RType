/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** method function for the lobby screen
*/

#include "LobbyScreen.hpp"

using Engine::LobbyScreen;

LobbyScreen::LobbyScreen(const Engine::Transform &transform, const bool scrollable):
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
	_buttons.push_back(Engine::Button({347, 242, 247, 45},
	{&Engine::GameEngine::open, false}));
	_buttons.push_back(Engine::Button({347, 315, 247, 45},
	{&Engine::GameEngine::open, false}));
	_buttons.push_back(Engine::Button({347, 386, 247, 45},
	{&Engine::GameEngine::open, false}));
}