/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Screen header which contain a displayer and a sceneScreen
*/

#ifndef SCREEN_HPP_
	#define SCREEN_HPP_

	#include <unordered_map>
	#include <map>
	#include "IDisplay.hpp"
	#include "ASceneScreen.hpp"
	#include "Component.hpp"
	#include "ButtonRequest.hpp"
	#include "IController.hpp"
	#include "ARenderer.hpp"
	#include "LobbyClient.hpp"

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
		void	displaySceneScreen() const noexcept;
		bool	isWindowOpen() const noexcept;
		const InputKey	&getInputKey() const noexcept;
		const Vector	&getClickPos() const noexcept;
		void		eventHandler() noexcept;
		char		getControllerKey() const noexcept;
		bool		isButtonPressed(const Vector &clickPos)
				noexcept;
		void		addButton(const Button &button) noexcept;
		void		addButton(const Rect &buttonPositon, const
				ButtonRequest &buttonRequest) noexcept;
		void		setButtons(std::vector<Button> buttons)
				noexcept;
		ARenderer	*createRenderer(const std::string
					&ressourcesPath)
					const noexcept;
		ARenderer	*createRenderer(const std::string
					&ressourcesPath,
					const Rect &spriteRectangle)
					const noexcept;
		ARenderer	*createRenderer(const std::string
					&ressourcesPath,
					const Rect &spriteRectangle,
					const Vector &moveRect)	
					const noexcept;
		ARenderer	*createRenderer(const std::string
					&ressourcesPath,
					const Rect &spriteRectangle,
					const Vector &moveRect,
					const unsigned int maxRepetition)
					const noexcept;
		void		refreshWindow() noexcept;
		void		displayLobbiesPlayer(std::map<std::string,
				LobbyClient>) noexcept;
		void		closeWindow() noexcept;
	private:
		void		drawLobbyInfo(const LobbyClient &lobby,
				const unsigned int &pos_y) noexcept;
		const IController &_controller;
		IDisplay	&_displayer;
		ASceneScreen	&_sceneScreen;
		ButtonRequest	_request = {"none", nullptr, false};
		InputKey	_inputKey = {false, 0, false};
		Vector		_clickPos = {0, 0};
	};
}

#endif /* !SCREEN_HPP_ */
