//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task move
//

#include "TaskMove.hpp"

using Engine::TaskMove;

// Ctor & Dtor
TaskMove::TaskMove(std::ifstream &stream)
: _move(stream)
{
	stream.read(reinterpret_cast<char*>(&_limited),
						sizeof(_limited));
}

TaskMove::TaskMove(const Engine::Vector &vec, bool limited)
: _move(vec), _limited(limited)
{
}

TaskMove::~TaskMove()
{
}

// Method
bool	TaskMove::execute(Engine::IComponent &compo) noexcept
{
	compo.getTransform().move(_move);
	return _limited;
}

void	TaskMove::serialize(std::ostream &stream) const noexcept
{
	unsigned int	id = 0;

	stream.write(reinterpret_cast<char*>(&id), sizeof(id));
	_move.serialize(stream);
	stream.write(reinterpret_cast<const char*>(&_limited),
						sizeof(_limited));
}