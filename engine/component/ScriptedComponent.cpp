//
// EPITECH PROJECT, 2018
// rtype
// File description:
// ScriptedComponent
//

#include "ScriptedComponent.hpp"
#include "ComponentException.hpp"

using Engine::ScriptedComponent;

ScriptedComponent::ScriptedComponent(Engine::GameEngine &engine,
bool friendly)
: Component(engine, friendly)
{
}

ScriptedComponent::ScriptedComponent(Engine::GameEngine &engine,
const Engine::Transform &transform, bool friendly)
: Component(engine, transform, friendly)
{
}

ScriptedComponent::ScriptedComponent(Engine::GameEngine &engine,
std::vector<Engine::ScriptObject::Task> &tasks, bool friendly)
: Component(engine, friendly), _script(tasks)
{
}

ScriptedComponent::ScriptedComponent(Engine::GameEngine &engine,
const Engine::Transform &transform,
std::vector<Engine::ScriptObject::Task> &tasks, bool friendly)
: Component(engine, transform, friendly), _script(tasks)
{
}

ScriptedComponent::~ScriptedComponent()
{
}

// Getter
Engine::ScriptObject	&ScriptedComponent::getScript() noexcept
{
	return _script;
}

// Method
void	ScriptedComponent::doTick()
{
	if (_brain != nullptr)
		_brain->doTick();
	try {
		_script.executeTask(*this);
	} catch (const Engine::ComponentException &e) {
	}
}