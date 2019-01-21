//
// EPITECH PROJECT, 2018
// rtype
// File description:
// translater
//

#include <fstream>
#include "Translater.hpp"
#include "TransPosition.hpp"
#include "TransSpawn.hpp"
#include "TransDeath.hpp"
#include "TransShoot.hpp"
#include "EngineException.hpp"

#include <iostream>

using Engine::Translater;

// Ctor & Dtor
Translater::Translater(Engine::GameEngine &engine,
Engine::SceneLoader &loader)
: _engine(engine), _loader(loader)
{
	_functions[0] = &Translater::makeTransPosition;
	_functions[1] = &Translater::makeTransSpawn;
	_functions[2] = &Translater::makeTransDeath;
	_functions[3] = &Translater::makeTransShoot;
}

// Method
void	Translater::clear() noexcept
{
	_actions.clear();
}

void	Translater::apply() noexcept
{
	for (const auto &action : _actions)
		action->apply();
	_actions.clear();
}

void	Translater::pushActions(std::ostream &stream)
{
	unsigned int	size = _actions.size();

	stream.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (const auto &action : _actions)
		action->serialize(stream);
	_actions.clear();
}

void	Translater::addAction(std::unique_ptr<Engine::ITranslate> &&action)
{
	_actions.push_back(std::move(action));
}

void	Translater::actionsFromStream(std::istream &stream)
{
	int	size = 0;
	int	id = 0;

	stream.read(reinterpret_cast<char*>(&size), sizeof(size));
	while (size > 0) {
		stream.read(reinterpret_cast<char*>(&id), sizeof(id));
		if (id >= TRANSLATE_NB)
			throw Engine::EngineException("ActionFromStream: "
			"Invalid id, unknown translation");
		(this->*_functions[id])(stream);
		--size;
	}
}

// Private method
void	Translater::makeTransSpawn(std::istream &stream)
{
	_actions.push_back(std::make_unique<Engine::TransSpawn>
						(_loader, stream));
}

void	Translater::makeTransDeath(std::istream &stream)
{
	_actions.push_back(std::make_unique<Engine::TransDeath>
						(_engine, stream));
}

void	Translater::makeTransShoot(std::istream &stream)
{
	_actions.push_back(std::make_unique<Engine::TransShoot>
						(_engine, stream));
}

void	Translater::makeTransPosition(std::istream &stream)
{
	_actions.push_back(std::make_unique<Engine::TransPosition>
						(_engine, stream));
}