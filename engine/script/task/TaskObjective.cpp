//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task objective
//

#include <cmath>
#include "TaskObjective.hpp"

using Engine::TaskObjective;

TaskObjective::TaskObjective(std::ifstream &stream)
: _objective(stream)
{
}

TaskObjective::TaskObjective(const Engine::Vector &objective)
: _objective(objective)
{
}

// Method
bool	TaskObjective::execute(Engine::IComponent &compo) noexcept
{
	Engine::Vector	pos = compo.getTransform().getPosition();
	float		speed = compo.getFeature().getSpeed();
	Engine::Vector	moving;
	bool		status;

	status = this->approachObjective(pos, speed, moving);
	if (status)
		compo.getTransform().place(_objective);
	else
		compo.getTransform().move(moving);
	return status;
}

void	TaskObjective::serialize(std::ostream &stream) const noexcept
{
	unsigned int	id = 1;

	stream.write(reinterpret_cast<char*>(&id), sizeof(id));
	_objective.serialize(stream);
}

// Private method
bool	TaskObjective::approachObjective(const Engine::Vector &start,
				float speed, Engine::Vector &move)
				const noexcept
{
	bool		ret = false;
	float		diff;

	move.setX(_objective.getX() - start.getX());
	move.setY(_objective.getY() - start.getY());
	diff = std::pow(move.getX(), 2) + std::pow(move.getY(), 2);
	diff = std::sqrt(diff);
	if (diff > speed) {
		move.setX(speed * move.getX() / diff);
		move.setY(speed * move.getY() / diff);
	} else
		ret = true;
	return (ret);
}
