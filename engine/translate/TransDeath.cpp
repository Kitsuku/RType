//
// EPITECH PROJECT, 2018
// rtype
// File description:
// trans death
//

#include <iostream>
#include "TransDeath.hpp"
#include "EngineException.hpp"

using Engine::TransDeath;

// Ctor
TransDeath::TransDeath(Engine::GameEngine &engine, std::istream &stream)
: _engine(&engine)
{
	stream.read(reinterpret_cast<char *>(&_id), sizeof(_id));
}

TransDeath::TransDeath(unsigned int id)
: _id(id)
{
}

// Method
void	TransDeath::apply() const
{
	if (_engine == nullptr)
		throw Engine::EngineException("TransDeath: "
		"Wrong Constructor for applying");
	try {
		_engine->killComponent(_id, true);
	} catch (const Engine::EngineException &e) {
		std::cerr << "Can't kill component " << _id << std::endl;
	}
}

void	TransDeath::serialize(std::ostream &stream) const noexcept
{
	const int	type = 2;

	stream.write(reinterpret_cast<const char*>(&type), sizeof(type));
	stream.write(reinterpret_cast<const char*>(&_id), sizeof(_id));
}