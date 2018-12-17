//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task shoot
//

#include "TaskShoot.hpp"

using Engine::TaskShoot;

// Ctor & Dtor
TaskShoot::TaskShoot(std::ifstream &stream)
: _target(stream)
{
}

TaskShoot::TaskShoot(const Engine::Vector &target)
: _target(target)
{
}

// Method
bool	TaskShoot::execute(Engine::IComponent &compo) noexcept
{
	compo.shoot(_target);
	return true;
}

void	TaskShoot::serialize(std::ostream &stream) const noexcept
{
	unsigned int	id = 2;

	stream.write(reinterpret_cast<char*>(&id), sizeof(id));
	_target.serialize(stream);
}