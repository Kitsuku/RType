//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task move
//

#ifndef TASKMOVE_HPP_
	#define TASKMOVE_HPP_

	#include "IComponent.hpp"
	#include "ITask.hpp"

namespace Engine {
	class TaskMove : public ITask {
	public:
		// Ctor & Dtor
		TaskMove(std::ifstream &stream);
		TaskMove(const Vector &vec, bool limited = true);
		virtual ~TaskMove() override;
		// Method
		bool	execute(IComponent &compo) noexcept override;
		void	serialize(std::ostream &s) const noexcept override;
	private:
		Vector	_move;
		bool	_limited;
	};
}

#endif /* !TASKMOVE_HPP_ */
