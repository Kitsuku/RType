//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scene loader
//

#ifndef SCENELOADER_HPP_
	#define SCENELOADER_HPP_

	#include <string>
	#include <chrono>

namespace Engine {
	class SceneLoader;
}

	#include "Scene.hpp"
	#include "GameEngine.hpp"
	#include "ActorLoader.hpp"

namespace Engine {
	class SceneLoader {
	public:
		using Clock = std::chrono::time_point<
						std::chrono::steady_clock>;
		// Ctor & Dtor
		SceneLoader(GameEngine &engine);
		~SceneLoader() = default;
		// Operator
		// Setter
		// Getter
		bool	isReading() const noexcept;
		// Method
		void	loadFromFile(const std::string &path);
		void	start() noexcept;
		void	stop() noexcept;
		void	doAction();
	private:
		// Private method
		void	applyFirst();
		void	applyAction();
		void	addComponent();
		// Attribut
		GameEngine	&_engine;
		ActorLoader	_loader;
		Scene		_scene;
		Clock		_start;
		bool		_started = false;
		bool		_reading = false;
		bool		_doneLast = false;
		SceneApparition	_action;
	};
}

#endif /* !SCENELOADER_HPP_ */
