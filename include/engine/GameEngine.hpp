//
// EPITECH PROJECT, 2018
// rtype
// File description:
// game engine
//

#ifndef GAMEENGINE_HPP_
	#define GAMEENGINE_HPP_

	#include <unordered_map>
	#include <memory>

namespace Engine {
	class GameEngine;
}

	#include "IDisplay.hpp"
	#include "IComponent.hpp"
	#include "PreComponent.hpp"
	#include "SceneLoader.hpp"
	#include "Objective.hpp"

namespace Engine {
	class GameEngine {
	public:
		using Element = std::unique_ptr<IComponent>;
		// Ctor & Dtor
		GameEngine(IDisplay *displayer = nullptr);
		~GameEngine() = default;
		// Setter
		// Getter
		const Vector	&getNearestComponentPos(const Vector &pos,
						bool team) const;
		// Method
		void	turn();
		void	open();
		void	addComponent(Element &&component);
		void	playScene(const std::string &path);
		void	createComponent(Element &&base,
				const PreComponent &data,
				IBrain *brain);
	private:
		using EMap = std::unordered_map<int, Element>;
		// Private method
		void	refreshComponents();
		// Attribut
		std::unique_ptr<SceneLoader>	_loader;
		EMap				_components;
		Objective			_objective;
		IDisplay			*_displayer;
		int				_offset = -1;
	};
}

#endif /* !GAMEENGINE_HPP_ */
