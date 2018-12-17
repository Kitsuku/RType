/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** LobbyScreen header to display screen with buttons
*/

#ifndef LOBBYSCREEN_HPP_
	#define LOBBYSCREEN_HPP_

	#include "ASceneScreen.hpp"

namespace Engine {
	class LobbyScreen: public ASceneScreen {
	public:
		// CTOR && DTOR
		LobbyScreen(const Engine::Transform &transform,
		const bool scrollable = false);
		LobbyScreen(Engine::ARenderer *renderer,
		const Engine::Transform &transform,
		const bool scrollable = false);
		~LobbyScreen();
	private:
		void	initButtons() noexcept;
	};
}

#endif /* !LOBBYSCREEN_HPP_ */
