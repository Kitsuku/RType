//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scriptobject
//

#include "ScriptObject.hpp"
#include "ComponentException.hpp"

using Engine::ScriptObject;

ScriptObject::ScriptObject()
{
}

ScriptObject::ScriptObject(std::vector<ScriptObject::Task> &tasks)
{
	this->setTasks(tasks);
}

// Operator
const ScriptObject::Task	&ScriptObject::operator[](int idx) const
{
	return _tasks[idx];
}

// Getter
unsigned int	ScriptObject::size() const noexcept
{
	return _tasks.size();
}

// Setter
void	ScriptObject::setTasks(std::vector<Task> &tasks) noexcept
{
	_tasks = std::move(tasks);
}

// Method
void	ScriptObject::executeTask(Engine::IComponent &compo)
{
	std::vector<ScriptObject::Task>::iterator	task;

	if (_tasks.size() == 0)
		throw ComponentException("No more task to execute");
	task = _tasks.begin();
	if ((*task)->execute(compo))
		_tasks.erase(task);
}

void	ScriptObject::addTask(Task &&task) noexcept
{
	_tasks.push_back(std::move(task));
}

void	ScriptObject::transfert(ScriptObject &obj) noexcept
{
	obj.setTasks(_tasks);
	_tasks.clear();
}

void	ScriptObject::clear() noexcept
{
	_tasks.clear();
}