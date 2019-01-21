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

	#include "Translater.hpp"
	#include "IDisplay.hpp"
	#include "IComponent.hpp"
	#include "PreComponent.hpp"
	#include "SceneLoader.hpp"
	#include "Objective.hpp"

	using EngineDura = std::chrono::duration<double, std::milli>;

namespace Engine {
	class GameEngine {
	public:
		using Element = std::unique_ptr<IComponent>;
		// Ctor & Dtor
		GameEngine(GameEngine&&) = default;
		GameEngine(IDisplay *displayer = nullptr);
		~GameEngine();
		// Setter
		void	setBoundingBox(ICollider *collider) noexcept;
		// Getter
		IComponent	&getComponentByID(int id);
		const Vector	&getNearestComponentPos(const Vector &pos,
							bool team) const;
		// Method
		void	turn();
		void	open();
		void	addComponent(Element &&component);
		void	playScene(const std::string &path,
						const EngineDura &asked);
		void	killComponent(int id, bool now = false);
		void	createComponent(Element &&base,
				const PreComponent &data);
		// Public attribut
		std::unique_ptr<Translater>	translater;
	private:
		using EMap = std::unordered_map<int, Element>;
		// Private method
		void	clearDead();
		void	refreshComponents();
		void	doCollision(const EMap::iterator &target);
		void	translatePosition(const IComponent &target);
		void	applyCollision(IComponent &first,
					IComponent &second) noexcept;
		// Attribut
		std::unique_ptr<SceneLoader>	_loader;
		EMap				_components;
		Objective			_objective;
		IDisplay			*_displayer;
		std::vector<int>		_toDeleteId;
		ICollider			*_box = nullptr;
	};
}

#endif /* !GAMEENGINE_HPP_ */
