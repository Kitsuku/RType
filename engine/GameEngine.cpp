//
// EPITECH PROJECT, 2018
// rtype
// File description:
// game engine
//

#include <iostream>
#include <chrono>
#include <thread>
#include "GameEngine.hpp"
#include "EngineException.hpp"
#include "DisplayException.hpp"
#include "TransPosition.hpp"
#include "TransDeath.hpp"
#include "Collider.hpp"

using Engine::GameEngine;
using std::this_thread::sleep_for;
using std::chrono::time_point;

GameEngine::GameEngine(Engine::IDisplay *displayer)
: _displayer(displayer)
{
	_loader = std::make_unique<Engine::SceneLoader>(*this);
	translater = std::make_unique<Engine::Translater>(*this,
							*_loader);
}

GameEngine::~GameEngine()
{
	if (_displayer != nullptr)
		delete _displayer;
	if (_box != nullptr)
		delete _box;
}

// Setter
void	GameEngine::setBoundingBox(Engine::ICollider *collider) noexcept
{
	_box = collider;
}

// Getter
Engine::IComponent	&GameEngine::getComponentByID(int id)
{
	EMap::iterator	target = _components.find(id);

	if (target == _components.end())
		throw Engine::EngineException("Target not found");
	return *target->second;
}

const Engine::Vector	&GameEngine::getNearestComponentPos(
				const Engine::Vector &pos, bool team) const
{
	(void) team;
	return pos;
}

// Method
void	GameEngine::turn()
{
	EMap::iterator	it = _components.begin();

	while (it != _components.end()) {
		it->second->doTick();
		if (it->second->getCollider() != nullptr)
			doCollision(it);
		translatePosition(*it->second);
		++it;
	}
	clearDead();
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

void	GameEngine::playScene(const std::string &path,
					const EngineDura &asked)
{
	time_point<std::chrono::system_clock>	start;
	time_point<std::chrono::system_clock>	end;
	EngineDura				diff(0);

	_loader->loadFromFile(path);
	_loader->start();
	while (!_objective.isOver()) {
		if (diff < asked)
			sleep_for(asked - diff);
		start = std::chrono::system_clock::now();
		if (_loader->isReading())
			_loader->doAction();
		turn();
		refreshComponents();
		end = std::chrono::system_clock::now();
		diff = end - start;
	}
	_loader->stop();
}

void	GameEngine::killComponent(int id, bool now)
{
	EMap::iterator	it;

	if (!now) {
		_toDeleteId.push_back(id);
		return;
	}
	it = _components.find(id);
	if (it == _components.end())
		throw Engine::EngineException("Target not found");
	if (it->second->isObjective())
		_objective.achieveOjective(it->second->isFriendly(),
						it->second->getID());
	translater->addAction(std::make_unique<Engine::TransDeath>(id));
	_components.erase(it);
}

void	GameEngine::createComponent(GameEngine::Element &&base,
				const Engine::PreComponent &data)
{
	ARenderer	*render = nullptr;

	if (_displayer != nullptr) {
		render = _displayer->createRenderer(data.path,
						data.rectangle);
		base->setARenderer(render);
	}
	if (data.colliding)
		base->setCollider(new Engine::Collider(*base,
						data.rectangle));
	base->setBrain(data.brain);
	base->setBullet(data.bullet);
	this->addComponent(std::move(base));
}

// Private method
void	GameEngine::clearDead()
{
	for (auto id : _toDeleteId)
		this->killComponent(id, true);
	_toDeleteId.clear();
}

void	GameEngine::refreshComponents()
{
	if (_displayer == nullptr)
		return;
	for (const auto &compo : _components) {
		try {
			_displayer->drawComponent(*compo.second);
		} catch (const Engine::DisplayException &e) {}
	}
	_displayer->display();
}

void	GameEngine::doCollision(const GameEngine::EMap::iterator &target)
{
	const Engine::ICollider	*collider = target->second->getCollider();
	const Engine::ICollider	*test = nullptr;

	if (_box && !_box->isColliding(*target->second->getCollider())) {
		killComponent(target->second->getID());
		return;
	}
	for (auto it = _components.begin(); it != _components.end(); ++it) {
		if (it == target || !target->second->getFeature().isAlive())
			continue;
		if (target->second->isFriendly() == it->second->isFriendly())
			continue;
		test = it->second->getCollider();
		if (test == nullptr || !collider->isColliding(*test))
			continue;
		applyCollision(*target->second, *it->second);
	}
}

void	GameEngine::translatePosition(const Engine::IComponent &target)
{
	if (!target.getFeature().isAlive()
	&& target.getFeature().isDeletable())
		return;
	translater->addAction(std::make_unique<Engine::TransPosition>
		(target.getID(), target.getTransform().getPosition()));
}

void	GameEngine::applyCollision(Engine::IComponent &first,
				Engine::IComponent &second) noexcept
{
	first.onColliding(second);
	second.onColliding(first);
	if (!second.getFeature().isAlive()) {
		if (second.getFeature().isDeletable())
			killComponent(second.getID());
	}
	if (!first.getFeature().isAlive()) {
		if (first.getFeature().isDeletable())
			killComponent(first.getID());
	}
}
