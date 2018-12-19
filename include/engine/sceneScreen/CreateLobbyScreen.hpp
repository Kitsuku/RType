/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** 
*/

#ifndef CREATELOBBYSCREEN_HPP_
	#define CREATELOBBYSCREEN_HPP_

	#include "ASceneScreen.hpp"

namespace Engine {
	class CreateLobbyScreen: public ASceneScreen {
	// CTOR && DTOR
	public:
		CreateLobbyScreen(const Engine::Transform &transform,
		const bool scrollable = false);
		CreateLobbyScreen(Engine::ARenderer *renderer,
		const Engine::Transform &transform,
		const bool scrollable = false);
		~CreateLobbyScreen();
	private:
		void	initButtons() noexcept;
	};
}

#endif /* !CREATELOBBYSCREEN_HPP_ */
