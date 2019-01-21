//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task factory
//

#include "TaskFactory.hpp"
#include "SceneException.hpp"
#include "TaskMove.hpp"
#include "TaskShoot.hpp"
#include "TaskObjective.hpp"
#include "TaskDirection.hpp"

using Engine::TaskFactory;

// Ctor & Dtor
TaskFactory::TaskFactory()
{
	_functions[0] = &TaskFactory::makeMove;
	_functions[1] = &TaskFactory::makeObjective;
	_functions[2] = &TaskFactory::makeShoot;
	_functions[3] = &TaskFactory::makeDirection;
}

TaskFactory::~TaskFactory()
{
}

// Method
TaskFactory::uITask	TaskFactory::make(std::ifstream &stream) const
{
	unsigned int	id;

	stream.read(reinterpret_cast<char*>(&id), sizeof(id));
	if (id >= NB_TASK)
		throw SceneException("Unknow task id");
	return (this->*_functions[id])(stream);
}

void			TaskFactory::fill(Engine::ScriptObject &script,
				std::ifstream &stream,
				unsigned int size) const
{
	for (unsigned int it = 0; it < size; ++it) {
		script.addTask(this->make(stream));
	}
}

// Private method
TaskFactory::uITask	TaskFactory::makeMove(std::ifstream &stream)
const
{
	return std::make_unique<TaskMove>(stream);
}

TaskFactory::uITask	TaskFactory::makeObjective(std::ifstream &stream)
const
{
	return std::make_unique<TaskObjective>(stream);
}

TaskFactory::uITask	TaskFactory::makeShoot(std::ifstream &stream)
const
{
	return std::make_unique<TaskShoot>(stream);
}

TaskFactory::uITask	TaskFactory::makeDirection(std::ifstream &stream)
const
{
	return std::make_unique<TaskDirection>(stream);
}