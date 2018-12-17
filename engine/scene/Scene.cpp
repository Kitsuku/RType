//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scene
//

#include <ctime>
#include "Scene.hpp"
#include "SceneException.hpp"

using Engine::Scene;

// Ctor & Dtor
Scene::~Scene()
{
	if (_file.is_open())
		_file.close();
}

// Getter
const std::vector<std::string>	&Scene::getActors() const noexcept
{
	return _path;
}

// Method
void	Scene::openFile(const std::string &path)
{
	if (_file.is_open()) {
		_file.close();
		_path.clear();
	}
	if (path.substr(path.length() - 4) != ".scn")
		throw SceneException("Bad file extension");
	_file.open(path, std::ios::binary);
	if (!_file.is_open())
		throw SceneException("Couldn't open the file");
	readActors();
}

const Engine::SceneApparition	Scene::readAction()
{
	Engine::SceneApparition	app;

	if (_file.eof())
		throw SceneException("No more apparition");
	_file.read(reinterpret_cast<char*>(&app.delta), sizeof(app.delta));
	_file.read(reinterpret_cast<char*>(&app.actor), sizeof(app.actor));
	if (app.delta == -1 || _file.eof())
		app.end = true;
	else
		app.script = readScript();
	return app;
}

// Private method
void			Scene::readActors()
{
	unsigned int	nbActor;
	unsigned int	size;
	std::string	path;

	_file.read(reinterpret_cast<char*>(&nbActor), sizeof(nbActor));
	for (unsigned int it = 0; it < nbActor; ++it) {
		_file.read(reinterpret_cast<char*>(&size), sizeof(size));
		if (size > 300)
			throw SceneException("Too long path size");
		addActor(size);
	}
}

Engine::ScriptObject	*Scene::readScript()
{
	Engine::ScriptObject	*script = nullptr;
	unsigned int		nbTask;

	_file.read(reinterpret_cast<char*>(&nbTask), sizeof(nbTask));
	if (nbTask > 0) {
		script = new Engine::ScriptObject;
		_facto.fill(*script, _file, nbTask);
	}
	return script;
}

void			Scene::addActor(unsigned int size)
{
	char	path[size + 1];

	_file.read(path, size);
	path[size] = '\0';
	_path.push_back(std::string(path));
}