/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Screen header which contain a displayer and a sceneScreen
*/

#ifndef SCREEN_HPP_
	#define SCREEN_HPP_

	#include <unordered_map>
	#include "IDisplay.hpp"
	#include "ASceneScreen.hpp"
	#include "Component.hpp"
	#include "ButtonRequest.hpp"
	#include "IController.hpp"
namespace Engine {
	class Screen {
	public:
		// CTOR && DTOR
		Screen(const IController &controller,
			IDisplay &displayer,
			ASceneScreen &ASceneScreen);
		~Screen() = default;
		// Getter
		const ButtonRequest	&getButtonRequest() const noexcept;
		// Setter
		void			setSceneScreen(const ASceneScreen
					&sceneScreen) noexcept;
		// Method
		void	displayGame(
			std::unordered_map
			<unsigned int, Component &> &mapComponent)
			const noexcept;
		bool	isWindowOpen() const noexcept;
		const InputKey	&getInputKey() const noexcept;
		const Vector	&getClickPos() const noexcept;
		void		eventHandler() noexcept;
		char		getControllerKey() const noexcept;
		//fonction qui call fait une requête au network
	private:
		const IController &_controller;
		IDisplay	&_displayer;
		ASceneScreen	&_sceneScreen;
		ButtonRequest	_request = {nullptr, false};
		InputKey	_inputKey = {false, 0, false};
		Vector		_clickPos = {0, 0};
	};
}

#endif /* !SCREEN_HPP_ */
