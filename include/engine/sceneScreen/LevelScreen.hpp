/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** LevelScreen header to display screen game
*/

#ifndef LEVELSCREEN_HPP_
	#define LEVELSCREEN_HPP_

class MasterClient;


	#include "ASceneScreen.hpp"

namespace Engine {
	class LevelScreen: public ASceneScreen {
	public:
		// CTOR && DTOR
		LevelScreen(const Engine::Transform &transform,
		const bool scrollable = false);
		LevelScreen(Engine::ARenderer *renderer,
		const Engine::Transform &transform,
		const bool scrollable = false);
		~LevelScreen();
	private:
		void	initButtons() noexcept;
	};
}

#endif /* !LEVELSCREEN_HPP_ */
