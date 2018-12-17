//
// EPITECH PROJECT, 2018
// rtype
// File description:
// objective
//

#include <array>
#include "Objective.hpp"
#include "EngineException.hpp"

using Engine::Objective;

// Getter
bool	Objective::getWinner() const
{
	if (_winner == -1)
		throw Engine::EngineException("No winner for the moment");
	return _winner;
}

// Setter
void	Objective::setWaiting() noexcept
{
	_waiting = true;
}

// Method
bool	Objective::isOver()
{
	bool	ret = false;

	if (_waiting)
		return ret;
	if (_teamA.empty()) {
		ret = true;
		_winner = 0;
	}
	if (_teamB.empty()) {
		if (ret)
			throw Engine::EngineException("Equality");
		ret = true;
		_winner = 1;
	}
	return ret;
}

void	Objective::achieveOjective(bool friendly, int id)
{
	if (friendly)
		_teamA.remove(id);
	else
		_teamB.remove(id);
}

void	Objective::addObjective(bool friendly, int id) noexcept
{
	if (friendly)
		_teamA.push_back(id);
	else
		_teamB.push_back(id);
	if (_waiting && _teamA.size() && _teamB.size())
		_waiting = false;
}
