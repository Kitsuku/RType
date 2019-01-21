//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task direction
//

#include "TaskDirection.hpp"

using Engine::TaskDirection;

// Ctor
TaskDirection::TaskDirection(std::ifstream &stream)
: _percent(stream)
{
	stream.read(reinterpret_cast<char*>(&_maxDist),
						sizeof(_maxDist));
}

TaskDirection::TaskDirection(float x, float y, float maxDist)
: _maxDist(maxDist)
{
	this->calcAttributs(x, y);
}

TaskDirection::TaskDirection(const Engine::Vector &direction)
{
	this->calcAttributs(direction.getX(), direction.getY());
}

// Method
bool	TaskDirection::execute(Engine::IComponent &compo)
noexcept
{
	Vector	moving(_percent);
	float	distance = compo.getFeature().getSpeed();
	bool	ret = false;

	if (_maxDist > 0) {
		if (_maxDist <= distance) {
			ret = true;
			distance = _maxDist;
		}
		_maxDist -= distance;
	}
	moving *= distance;
	compo.getTransform().move(moving);
	return ret;
}

void	TaskDirection::serialize(std::ostream &stream)
const noexcept
{
	unsigned int	id = 3;

	stream.write(reinterpret_cast<char*>(&id), sizeof(id));
	stream.write(reinterpret_cast<const char*>(&_percent),
						sizeof(_percent));
	stream.write(reinterpret_cast<const char*>(&_maxDist),
						sizeof(_maxDist));
}

// Private method
void	TaskDirection::calcAttributs(float x, float y)
{
	float	sum = std::abs(x) + std::abs(y);

	if (x != 0)
		_percent.setX(sum / x);
	if (y != 0)
		_percent.setY(sum / y);
}