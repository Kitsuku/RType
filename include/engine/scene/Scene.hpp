//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scene
//

#ifndef SCENE_HPP_
	#define SCENE_HPP_

	#include <string>
	#include <fstream>
	#include <vector>

	#include "TaskFactory.hpp"
	#include "SceneApparition.hpp"

namespace Engine {
	class Scene {
	public:
		// Ctor & Dtor
		Scene() = default;
		~Scene();
		// Getter
		const std::vector<std::string>	&getActors()
						const noexcept;
		// Method
		const SceneApparition	readAction();
		void			openFile(const std::string &path);
	private:
		// Private method
		void		readActors();
		ScriptObject	*readScript();
		void		addActor(unsigned int size);
		// Attribut
		TaskFactory			_facto;
		std::ifstream			_file;
		std::vector<std::string>	_path;
	};
}

#endif /* !SCENE_HPP_ */
