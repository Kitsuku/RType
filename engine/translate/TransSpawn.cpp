//
// EPITECH PROJECT, 2018
// rtype
// File description:
// trans spawn
//

#include "TransSpawn.hpp"
#include "EngineException.hpp"

using Engine::TransSpawn;

// Ctor & Dtor
TransSpawn::TransSpawn(Engine::SceneLoader &loader, std::istream &stream)
: _loader(&loader)
{
	stream.read(reinterpret_cast<char*>(&_id), sizeof(_id));
	stream.read(reinterpret_cast<char*>(&_apparition),
						sizeof(_apparition));
}

TransSpawn::TransSpawn(unsigned int id, const TransSpawn::AppActor &app)
: _id(id), _apparition(app)
{
}

// Method
void	TransSpawn::apply() const
{
	if (_loader == nullptr)
		throw Engine::EngineException("TransSpawn: "
		"Wrong Constructor for applying");
	_loader->createByApparition(_id, _apparition);
}

void	TransSpawn::serialize(std::ostream &stream) const noexcept
{
	const int	type = 1;

	stream.write(reinterpret_cast<const char*>(&type), sizeof(type));
	stream.write(reinterpret_cast<const char*>(&_id), sizeof(_id));
	stream.write(reinterpret_cast<const char*>(&_apparition),
						sizeof(_apparition));
}