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
const Engine::SceneApparition	Scene::readAction()
{
	Engine::SceneApparition	app;

	if (!_file.is_open())
		throw Engine::SceneException("No file openned");
	if (_file.eof())
		throw Engine::SceneException("No more apparition");
	_file.read(reinterpret_cast<char*>(&app.delta), sizeof(app.delta));
	_file.read(reinterpret_cast<char*>(&app.actor), sizeof(app.actor));
	if (app.delta == -1 || _file.eof())
		app.end = true;
	else
		app.script = readScript();
	return app;
}

void	Scene::openFile(const std::string &path)
{
	if (_file.is_open()) {
		_file.close();
		_path.clear();
	}
	if (path.substr(path.length() - 4) != ".scn")
		throw Engine::SceneException("Bad file extension");
	_file.open(path, std::ios::binary);
	if (!_file.is_open())
		throw Engine::SceneException("Couldn't open the file");
	readActors(_file);
}

void	Scene::loadFromStream(std::istream &stream) noexcept
{
	readActors(stream);
}

void	Scene::serializeActors(std::ostream &stream) const
{
	std::size_t	size = _path.size();

	if (size == 0)
		throw Engine::SceneException("No Actor to serialize");
	stream.write(reinterpret_cast<char*>(&size), sizeof(size));
	for (const std::string &path : _path) {
		size = path.size();
		stream.write(reinterpret_cast<char*>(&size), sizeof(size));
		stream.write(path.c_str(), size);
	}
}

// Private method
void			Scene::readActors(std::istream &stream)
{
	unsigned int	nbActor;
	unsigned int	size;
	std::string	path;

	stream.read(reinterpret_cast<char*>(&nbActor), sizeof(nbActor));
	for (unsigned int it = 0; it < nbActor; ++it) {
		stream.read(reinterpret_cast<char*>(&size), sizeof(size));
		if (size > 300)
			throw Engine::SceneException("Too long path size");
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
	char	path[100];

	_file.read(path, size);
	path[size] = '\0';
	_path.push_back(std::string(path));
}