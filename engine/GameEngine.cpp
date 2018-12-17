//
// EPITECH PROJECT, 2018
// rtype
// File description:
// game engine
//
#include <iostream>
#include "GameEngine.hpp"
#include "EngineException.hpp"

using Engine::GameEngine;

GameEngine::GameEngine(Engine::IDisplay *displayer)
: _displayer(displayer)
{
	_loader = std::make_unique<SceneLoader>(*this);
}

// Method
void	GameEngine::turn()
{
	for (auto &obj : _components) {
		(*obj.second).doTick();
	}
}

void	GameEngine::open()
{
	if (_displayer)
		_displayer->createWindow(true, "R-type");
	std::cout << "success call to start" << std::endl;
}

void	GameEngine::addComponent(GameEngine::Element &&component)
{
	int	id = component->getID();

	if (component->isObjective())
		_objective.addObjective(component->isFriendly(), id);
	_components[id] = std::move(component);
}

#include <iostream>
void	GameEngine::playScene(const std::string &path)
{
	_loader->loadFromFile(path);
	_loader->start();
	int i = 0;
	while (!_objective.isOver()) {
		if (_loader->isReading())
			_loader->doAction();
		else {
			_objective.achieveOjective(true, i);
			++i;
		}
		turn();
		refreshComponents();
	}
	std::cout << "Winner team " << _objective.getWinner()
	<< std::endl;
	_loader->stop();
}

void	GameEngine::createComponent(GameEngine::Element &&base,
				const Engine::PreComponent &data,
				Engine::IBrain *brain)
{
	ARenderer	*render = nullptr;

	if (_displayer != nullptr) {
		render = _displayer->createRenderer(data.path,
						data.rectangle);
		base->setARenderer(render);
	}
	base->setBrain(brain);
	this->addComponent(std::move(base));
}

// Private method
void	GameEngine::refreshComponents()
{
	//
	if (_displayer == nullptr)
		return;
	for (const auto &compo : _components)
		_displayer->drawComponent(*compo.second);
	_displayer->display();
}
