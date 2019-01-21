//
// EPITECH PROJECT, 2018
// rtype
// File description:
// main
//

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <thread>

#include "GameEngine.hpp"
#include "SfmlDisplay.hpp"
#include "ScriptedComponent.hpp"
#include "SfmlController.hpp"
#include "exception/ComponentException.hpp"
#include "TaskDirection.hpp"
#include "TaskObjective.hpp"
#include "TaskShoot.hpp"
#include "TaskMove.hpp"
#include "SceneApparition.hpp"
#include "SceneLoader.hpp"
#include "Button.hpp"
#include "Rect.hpp"
#include "MenuScreen.hpp"
#include "Screen.hpp"
#include "Launcher.hpp"
#include "ColliderStatic.hpp"

void	setActor(std::ostream &stream, const std::vector<std::string> &path)
{
	unsigned int size = path.size();

	stream.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (const auto &p : path) {
		size = p.size();
		stream.write(reinterpret_cast<char*>(&size), sizeof(size));
		stream.write(p.c_str(), size);
	}
}

void	appear(std::ostream &s, Engine::SceneApparition &app,
			Engine::ScriptObject *so = nullptr)
{
	unsigned int	size = 0;
	s.write(reinterpret_cast<char*>(&app.delta), sizeof(app.delta));
	s.write(reinterpret_cast<char*>(&app.actor), sizeof(app.actor));
	if (so != nullptr)
		size = so->size();
	s.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (unsigned int it = 0; it < size; ++it) {
		(*so)[it]->serialize(s);

	}
}

/* int main()
int main()
{
	Engine::GameEngine engine(new Engine::SfmlDisplay);
	Engine::ColliderStatic	*box = new Engine::ColliderStatic(Engine::Vector(0, 0),
								Engine::Vector(1200, 1000));

	//build_level_one();
	engine.setBoundingBox(box);
	engine.open();
	engine.playScene("level00.scn", EngineDura(0.1));
	return 0;
} */


/* int main()
{
		Engine::SfmlDisplay sfmlDisplay;


	Engine::GameEngine gameEngine;
	Engine::Component	component(gameEngine, true);
	Engine::Component	component_2(gameEngine, true);
	Engine::Transform	transform({200, 200}, {0, 0}, {2, 2});
	Engine::Transform	transform_2({400, 400}, {0, 0}, {2, 2});
	Engine::SfmlController	sfmlController;
	const Rect		tata = {200, 200, 100, 100};

	//Engine::LobbyScreen	lobbyScreen(Engine::Transform({0 ,0}, {0 ,0}, {1, 1}));
	Rect spriteRect = {0, 0, 33, 33};
	Engine::Vector vectorMove(33, 0);
	unsigned int repetition = 2;

	component.getTransform() = transform;
	component_2.getTransform() = transform_2;
	sfmlDisplay.createWindow(960, 600, "R-type");
	Engine::ARenderer *renderer = sfmlDisplay.createRenderer("r-typesheet7.gif");
	Engine::ARenderer *renderer_2 = sfmlDisplay.createRenderer("r-typesheet7.gif");
	Engine::ARenderer *renderer_menu = sfmlDisplay.createRenderer("menu.gif", {0, 0, 960, 600}, {0, 0}, {0});
	Engine::ARenderer *renderer_room = sfmlDisplay.createRenderer("room.gif", {0, 0, 960, 600}, {0, 0}, {0});

	lobbyScreen.setARenderer(renderer_menu);
	otherScreen.setARenderer(renderer_room);
	renderer->show();
	renderer->setOpacity(255);
	renderer->setVectorMove(vectorMove);
	renderer->setMaxRepetition(repetition);
	renderer->setSpriteRect(spriteRect);
	component.setARenderer(renderer);

	renderer_2->show();
	renderer_2->setOpacity(255);
	renderer_2->setVectorMove(vectorMove);
	renderer_2->setMaxRepetition(repetition);
	renderer_2->setSpriteRect(spriteRect);
	component_2.setARenderer(renderer_2);

	std::unordered_map <unsigned int, Engine::Component &> mapComponent = {
		{0, component},
		{1, component_2}
	};
	Engine::SfmlController	toto;

	Engine::Screen	screen(toto, sfmlDisplay, lobbyScreen);



	int i = 0;
	while (screen.isWindowOpen()) {
		InputKey key = screen.getInputKey();
		Engine::Vector clickpos = screen.getClickPos();
		screen.eventHandler();
		screen.displayGame(mapComponent);
		if (i == 5000) {
			screen.setSceneScreen(otherScreen);
		}
		++i;
		char toto = screen.getControllerKey();
		if (toto != '0') {
			std::cout << "key value : " << toto << std::endl;
		}
		if (clickpos.getX() != 0 && clickpos.getX() != 0) {
			std::cout << "pos_x: " << clickpos.getX() << 
			" and pos_y: " << clickpos.getY() << std::endl;
		}
		if (lobbyScreen.isPressed(clickpos)) {
			const ButtonRequest test= lobbyScreen.getRequest();
			std::cout << "value of the bool is : " << test.needRequest << std::endl;
			(gameEngine.*test.fptr)();
		}
	}
	return 0;
} */

//main masterclient
int main(int ac, const char **av)
{
	Engine::SfmlController	sfmlController;
	std::string		path(av[0]);
	Engine::SfmlDisplay	sfmlDisplayer(path);
	Launcher		launcher(ac, av,
				sfmlController, sfmlDisplayer);
	if (!launcher.isError()) {
		return 84;
	}
	try {
		launcher.launch();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
        	return 84;
	}
}