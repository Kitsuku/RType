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
#include "TransSpawn.hpp"

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
void	SceneLoader::loadFromFile(const std::string &path) noexcept
{
	_scene.openFile(path);
	for (const auto &actor : _scene.getActors()) {
		_loader.addActor(std::string("entities/") + actor);
	}
}

void	SceneLoader::loadFromHeader(std::istream &stream) noexcept
{
	_scene.loadFromStream(stream);
}

void	SceneLoader::serializeHeader(std::ostream &stream) noexcept
{
	_scene.serializeActors(stream);
}

void	SceneLoader::createByApparition(unsigned int id,
const Engine::SceneApparition::SceneActor &actor)
{
	Engine::IComponent	*component = nullptr;

	component = new Engine::Component(_engine, actor.transform,
							actor.team);
	component->setID(id);
	component->setObjective(actor.objective);
	_engine.addComponent(Engine::GameEngine::Element(component));
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
	auto			compo = createComponent();

	compo->setObjective(_action.actor.objective);
	_engine.translater->addAction(std::make_unique<Engine::TransSpawn>
					(compo->getID(), _action.actor));
	_engine.createComponent(Engine::GameEngine::Element(compo), app);
}

Engine::IComponent	*SceneLoader::createComponent()
{
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
	return compo;
}