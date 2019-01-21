/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** method function for the level 1 screen
*/

#include "LevelScreen.hpp"
#include "MasterClient.hpp"

using Engine::LevelScreen;

LevelScreen::LevelScreen(const Engine::Transform &transform,
const bool scrollable):
ASceneScreen(transform, scrollable)
{
	initButtons();
}

LevelScreen::LevelScreen(Engine::ARenderer *renderer,
const Engine::Transform &transform, const bool scrollable):
ASceneScreen(renderer, transform, scrollable)
{
	initButtons();
}

LevelScreen::~LevelScreen()
{
}

// Private
void	LevelScreen::initButtons() noexcept
{
}