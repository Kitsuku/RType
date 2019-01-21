//
// EPITECH PROJECT, 2018
// rtype
// File description:
// taskfactory
//

#ifndef TASKFACTORY_HPP_
	#define TASKFACTORY_HPP_

	#include <memory>

namespace Engine {
	class TaskFactory;
}

	#include "ScriptObject.hpp"

	#define NB_TASK		4

namespace Engine {
	class TaskFactory {
	public:
		// Ctor & Dtor
		TaskFactory();
		~TaskFactory();
		// Method
		std::unique_ptr<ITask>	make(std::ifstream &stream) const;
		void			fill(ScriptObject &script,
					std::ifstream &streamn,
					unsigned int size) const;
	private:
		using uITask = std::unique_ptr<ITask>;
		using f = uITask (TaskFactory::*)(std::ifstream&) const;
		// Private method
		uITask	makeMove(std::ifstream &stream) const;
		uITask	makeObjective(std::ifstream &stream) const;
		uITask	makeShoot(std::ifstream &stream) const;
		uITask	makeDirection(std::ifstream &stream) const;
		// Attribut
		std::array<f, NB_TASK>	_functions;
	};
}

#endif /* !TASKFACTORY_HPP_ */
