/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** MenuScreen header to display screen with buttons
*/

#ifndef MENUSCREEN_HPP_
	#define MENUSCREEN_HPP_

class MasterClient;


	#include "ASceneScreen.hpp"

namespace Engine {
	class MenuScreen: public ASceneScreen {
	public:
		// CTOR && DTOR
		MenuScreen(const Engine::Transform &transform,
		const bool scrollable = false);
		MenuScreen(Engine::ARenderer *renderer,
		const Engine::Transform &transform,
		const bool scrollable = false);
		~MenuScreen();
	private:
		void	initButtons() noexcept;
	};
}

#endif /* !MENUSCREEN_HPP_ */
