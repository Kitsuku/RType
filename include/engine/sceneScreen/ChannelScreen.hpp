/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** SceneScreen header for channel
*/

#ifndef CHANNELSCREEN_HPP_
	#define CHANNELSCREEN_HPP_

	#include "ASceneScreen.hpp"

namespace Engine {
	class ChannelScreen: public ASceneScreen {
	public:
		// CTOR && DTOR
		ChannelScreen(const Engine::Transform &transform,
		const bool scrollable = false);
		ChannelScreen(Engine::ARenderer *renderer,
		const Engine::Transform &transform,
		const bool scrollable = false);
		~ChannelScreen();
	private:
		void	initButtons() noexcept;
	};
}

#endif /* !CHANNELSCREEN_HPP_ */
