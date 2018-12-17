//
// EPITECH PROJECT, 2018
// rtype
// File description:
// actor loader
//

#include <iostream>
#include <dlfcn.h>
#include "ActorLoader.hpp"
#include "SceneException.hpp"

using Engine::ActorLoader;

// Ctor & Dtor
ActorLoader::ActorLoader()
{
}

ActorLoader::~ActorLoader()
{
	this->reset();
}

// Operator
Engine::PreComponent	ActorLoader::operator[](unsigned idx) const
{
	return _actors[idx]();
}

// Method
void	ActorLoader::reset() noexcept
{
	_actors.clear();
	for (auto handle : _handlers) {
		dlclose(handle);
	}
	_handlers.clear();
}

void	ActorLoader::addActor(const std::string &path)
{
	void	*handle;

	handle = dlopen(path.c_str(), RTLD_LAZY);
	if (dlerror() != nullptr || !handle) {
		throw Engine::SceneException(std::string("Could not load ")
		+ path.c_str() + " Actor Library");
	}
	stackActor(handle);
}

// Private method
void	ActorLoader::stackActor(void *handle)
{
	ActorLoader::ptr	func;

	func = (ActorLoader::ptr)(dlsym(handle, "build"));
	if (dlerror() != nullptr)
		throw Engine::SceneException("Could not find 'build'"
		" function in Actor Library");
	_handlers.push_back(handle);
	_actors.push_back(func);
}