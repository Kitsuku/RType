//
// EPITECH PROJECT, 2018
// rtype
// File description:
// trans shoot
//

#include "TransShoot.hpp"
#include "EngineException.hpp"
#include <iostream>

using Engine::TransShoot;

// Ctor
TransShoot::TransShoot(Engine::GameEngine &engine, std::istream &stream)
: _engine(&engine)
{
	stream.read(reinterpret_cast<char*>(&_id), sizeof(_id));
}

TransShoot::TransShoot(unsigned int id, const Engine::Vector &target)
: _id(id), _target(target)
{
}

// Method
void	TransShoot::apply() const
{
	IComponent	*compo = nullptr;

	if (_engine == nullptr)
		throw Engine::EngineException("TransShoot: "
		"Wrong Constructor for applying");
	try {
		compo = &_engine->getComponentByID(_id);
		compo->shoot(_target);
	} catch (const Engine::EngineException &e) {
		std::cerr << "Shoot: Can't find component "
		<< _id << std::endl;
	}
}

void	TransShoot::serialize(std::ostream &stream) const noexcept
{
	const int	type = 3;

	stream.write(reinterpret_cast<const char*>(&type), sizeof(type));
	stream.write(reinterpret_cast<const char*>(&_id), sizeof(_id));
}
