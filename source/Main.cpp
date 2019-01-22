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