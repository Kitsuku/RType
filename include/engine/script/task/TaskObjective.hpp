//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task objective
//

#ifndef TASKOBJECTIVE_HPP_
	#define TASKOBJECTIVE_HPP_

	#include <fstream>

	#include "Vector.hpp"
	#include "IComponent.hpp"
	#include "ITask.hpp"

namespace Engine {
	class TaskObjective : public ITask {
	public:
		// Ctor & Dtor
		TaskObjective(std::ifstream &stream);
		TaskObjective(const Vector &objective);
		~TaskObjective() override = default;
		// Method
		bool	execute(IComponent &compo) noexcept override;
		void	serialize(std::ostream &s) const noexcept override;
	private:
		// Private method
		bool approachObjective(const Vector &start, float speed,
					Vector &moving) const noexcept;
		// Attribut
		Vector	_objective;
	};
}

#endif /* !TASKOBJECTIVE_HPP_ */
