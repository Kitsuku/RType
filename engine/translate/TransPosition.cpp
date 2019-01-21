//
// EPITECH PROJECT, 2018
// rtype
// File description:
// trans position
//

#include "TransPosition.hpp"
#include "EngineException.hpp"

using Engine::TransPosition;

// Ctor & Dtor
TransPosition::TransPosition(Engine::GameEngine &engine,
std::istream &stream)
: _engine(&engine), _position(stream)
{
	stream.read(reinterpret_cast<char*>(&_id), sizeof(_id));
}

TransPosition::TransPosition(int id, const Engine::Vector &position)
: _id(id), _position(position)
{
}

// Method
void	TransPosition::apply() const
{
	if (_engine == nullptr)
		throw Engine::EngineException("TransPosition: "
		"Wrong Constructor for applying");
	_engine->getComponentByID(_id).getTransform().place(_position);
}

void	TransPosition::serialize(std::ostream &stream) const noexcept
{
	const int	type = 0;

	stream.write(reinterpret_cast<const char*>(&type), sizeof(type));
	_position.serialize(stream);
	stream.write(reinterpret_cast<const char*>(&_id), sizeof(_id));
}