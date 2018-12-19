/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** object parsing main arguments
*/
#include <thread>
#include <iostream>

#include "MenuScreen.hpp"
#include "CreateLobbyScreen.hpp"
#include "SfmlDisplay.hpp"
#include "Screen.hpp"
#include "Launcher.hpp"
#include "MasterClient.hpp"
#include "SfmlController.hpp"

// CTOR
Launcher::Launcher(int ac, const char **args,
Engine::IController &controller, Engine::IDisplay &displayer): _args(args),
_controller(controller), _displayer(displayer)
{
	if (ac != 3) {
		std::cerr << "Usage: client <host>" << std::endl;
	} else {
		_error = true;
	}
}

// Getter
const bool		&Launcher::isError() const noexcept
{
	return _error;
}
#include <iostream>
// Method
void			Launcher::launch()
{
	Engine::MenuScreen	init_screen(createInitialRenderer(),
				Engine::Transform({0, 0}, {0, 0}, {1, 1}));
	Engine::Screen		screen(_controller, _displayer, init_screen);
	Engine::GameEngine	gameEngine(&_displayer);
	boost::asio::io_service	io;
        udp::resolver		resolver(io);
        UdpClient		udpClient(_args[1], _args[2], io);

	_displayer.createWindow(true, "R-type");
	_displayer.setFont();
    	udpClient.start(resolver.resolve(udp::resolver::query(udp::v4(),
	_args[1], _args[2])));
    io.poll_one();
	std::thread runClient([&io] {
		io.run();
	});
	instantiateMaster(screen, udpClient, gameEngine);
	runClient.join();
}

// Private
Engine::ARenderer	*Launcher::createInitialRenderer() const noexcept
{
	return _displayer.createRenderer("menu.gif",
		{0, 0, 960, 600}, {0, 0}, {0});
}

void			Launcher::instantiateMaster(Engine::Screen &screen,
			UdpClient &udpClient, Engine::GameEngine &gameEngine)
			noexcept
{
	Engine::MenuScreen	menuScreen(
				Engine::Transform({0, 0}, {0, 0}, {1, 1}));
	Engine::ChannelScreen	channelScreen(
				Engine::Transform({0, 0}, {0, 0}, {1, 1}));
	Engine::CreateLobbyScreen	createLobbyScreen(Engine::Transform(
					{0, 0}, {0, 0}, {1, 1}));
	std::unordered_map <unsigned int, Engine::ASceneScreen &>
								sceneScreens;

	sceneScreens.insert({{1, menuScreen}, {2, channelScreen},
	{3, createLobbyScreen}});
	setSceneScreenRenderer(screen, sceneScreens);
	MasterClient(_args[0], screen, udpClient, gameEngine, sceneScreens)
	.gameLoop();
}

void			Launcher::setSceneScreenRenderer(Engine::Screen
			&screen, std::unordered_map
			<unsigned int, Engine::ASceneScreen &> &sceneScreens)
			noexcept
{
	Engine::ARenderer	*menuRenderer = screen.createRenderer(
				"screen-main.gif", {0, 0, 1920, 1200},
				{0, 0}, {0});
	Engine::ARenderer	*roomsRenderer =
				screen.createRenderer("screen-join-refresh.gif",
				{0, 0,  1920, 1200}, {0, 0}, {0});
	Engine::ARenderer	*createLobbyRenderer =
				screen.createRenderer("screen-create.gif",
				{0, 0,  1920, 1200}, {0, 0}, {0});

	sceneScreens.at(1).setARenderer(menuRenderer);
	sceneScreens.at(2).setARenderer(roomsRenderer);
	sceneScreens.at(3).setARenderer(createLobbyRenderer);
}