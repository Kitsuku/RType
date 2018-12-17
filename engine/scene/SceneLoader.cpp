//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scene loader
//

#include <ostream>
#include "SceneLoader.hpp"
#include "SceneException.hpp"
#include "ScriptedComponent.hpp"

using Engine::SceneLoader;

// Ctor & Dtor
SceneLoader::SceneLoader(Engine::GameEngine &engine)
: _engine(engine)
{
}

// Getter
bool	SceneLoader::isReading() const noexcept
{
	return (_started && _reading);
}

// Method
void	SceneLoader::loadFromFile(const std::string &path)
{
	_scene.openFile(path);
	for (const auto &actor : _scene.getActors()) {
		_loader.addActor(std::string("entities/") + actor);
	}
}

void	SceneLoader::start() noexcept
{
	_started = true;
	_reading = true;
	applyFirst();
	_start = std::chrono::steady_clock::now();
}

void	SceneLoader::stop() noexcept
{
	_started = false;
	_reading = false;
}

void	SceneLoader::doAction()
{
	if (!_started)
		throw SceneException("Scene loader is not Started");
	if (!_reading)
		return;
	if (_doneLast) {
		_action = _scene.readAction();
		if (_action.end == true) {
			_reading = false;
			return;
		}
		_doneLast = false;
	}
	applyAction();
}

// Private method
void	SceneLoader::applyFirst()
{
	while (true) {
		_action = _scene.readAction();
		if (_action.delta > 0 || _action.end)
			break;
		addComponent();
	}
	if (_action.end)
		_reading = false;
}

void	SceneLoader::applyAction()
{
	std::chrono::duration<double, std::ratio<1, 1000>> delta;

	delta = std::chrono::steady_clock::now() - _start;
	if (_action.delta < delta.count()) {
		_doneLast = true;
		addComponent();
	}
}

void	SceneLoader::addComponent()
{
	auto			app = _loader[_action.actor.actor];
	bool			team = _action.actor.team;
	ScriptedComponent	*scompo = nullptr;
	IComponent		*compo = nullptr;

	if (_action.script != nullptr) {
		scompo = new Engine::ScriptedComponent(_engine,
					_action.actor.transform, team);
		_action.script->transfert(scompo->getScript());
		compo = scompo;
		delete _action.script;
	} else
		compo = new Engine::Component(_engine,
				_action.actor.transform, team);
	compo->setObjective(_action.actor.objective);
	compo->setBullet(app.bullet);
	_engine.createComponent(Engine::GameEngine::Element(compo), app,
							app.brain);
}