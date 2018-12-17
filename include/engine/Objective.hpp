//
// EPITECH PROJECT, 2018
// rtype
// File description:
// objective
//

#ifndef OBJECTIVE_HPP_
	#define OBJECTIVE_HPP_

	#include <memory>
	#include <list>

namespace Engine {
	class Objective {
	public:
		// Ctor & Dtor
		Objective() = default;
		~Objective() = default;
		// Getter
		bool	getWinner() const;
		// Setter
		void	setWaiting() noexcept;
		// Method
		bool	isOver();
		void	achieveOjective(bool friendly, int id);
		void	addObjective(bool friendly, int id) noexcept;
	private:
		std::list<int>	_teamA;
		std::list<int>	_teamB;
		int		_winner = -1;
		bool		_waiting = true;
	};
}

#endif /* !OBJECTIVE_HPP_ */
