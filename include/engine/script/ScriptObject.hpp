//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scriptobject
//

#ifndef SCRIPTOBJECT_HPP_
	#define SCRIPTOBJECT_HPP_

	#include <vector>

namespace Engine {
	class ScriptObject;
}
	#include <memory>
	#include "ITask.hpp"

namespace Engine {
	class ScriptObject {
	public:
		using Task = std::unique_ptr<ITask>;
		// Ctor & Dtor
		ScriptObject();
		ScriptObject(std::vector<Task> &tasks);
		~ScriptObject() = default;
		// Operator
		const Task	&operator[](int idx) const;
		// Setter
		void	setTasks(std::vector<Task> &tasks) noexcept;
		// Getter
		unsigned int	size() const noexcept;
		// Method
		void	executeTask(IComponent &compo);
		void	addTask(Task &&task) noexcept;
		void	transfert(ScriptObject &obj) noexcept;
		void	clear() noexcept;
	private:
		std::vector<Task>	_tasks;
	};
}

#endif /* !SCRIPTOBJECT_HPP_ */
