/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Object parsing main arguments
*/

#ifndef LAUNCHER_HPP_
	#define LAUNCHER_HPP_

	#include "MasterClient.hpp"
	#include "ARenderer.hpp"
	#include "IController.hpp"
	#include "IDisplay.hpp"

class Launcher {
public:
	// CTOR && DTOR
	Launcher(int ac, const char **av, Engine::IController &controller,
	Engine::IDisplay &displayer);
	~Launcher() = default;
	// Getter
	const bool	&isError() const noexcept;
	// Method
	void		launch();

private:
	Engine::ARenderer	*createInitialRenderer() const noexcept;
	void			instantiateMaster(Engine::Screen &screen,
				UdpClient &udpClient,
				Engine::GameEngine &gameEngine)	noexcept;
	void			insertOtherScreen(Engine::Screen
				&screen, UdpClient &udpClient,
				Engine::GameEngine &gameEngine)
				noexcept;
	void			setSceneScreenRenderer(Engine::Screen &screen)
				noexcept;
	void			setLevelRenderer(Engine::Screen &screen)
				noexcept;
	const char		**_args;
	Engine::IController	&_controller;
	Engine::IDisplay	&_displayer;
	std::unordered_map <unsigned int, Engine::ASceneScreen &>
				_sceneScreens;
	bool		_error = false;
};

#endif /* !LAUNCHER_HPP_ */
