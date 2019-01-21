//
// EPITECH PROJECT, 2018
// rtype
// File description:
// translater
//

#ifndef TRANSLATER_HPP_
	#define TRANSLATER_HPP_

	#include <vector>
	#include <ostream>
	#include <memory>
	#include <array>

	#include "ITranslate.hpp"

	#define TRANSLATE_NB	4

namespace Engine {
	class GameEngine;	// To avoid circular
	class SceneLoader;	// include issues
	class Translater {
	public:
		// Ctor & Dtor
		Translater(GameEngine &engine, SceneLoader &loader);
		~Translater() = default;
		// Method
		void	clear() noexcept;
		void	apply() noexcept;
		void	pushActions(std::ostream &stream);
		void	addAction(std::unique_ptr<ITranslate> &&action);
		void	actionsFromStream(std::istream &stream);
	private:
		using f = void (Translater::*)(std::istream&);
		using ActionList = std::vector<std::unique_ptr<ITranslate>>;
		// Private method
		void	makeTransSpawn(std::istream &stream);
		void	makeTransDeath(std::istream &stream);
		void	makeTransShoot(std::istream &stream);
		void	makeTransPosition(std::istream &stream);
		// Attribut
		GameEngine			&_engine;
		SceneLoader			&_loader;
		ActionList			_actions;
		std::array<f, TRANSLATE_NB>	_functions;
	};
}

#endif /* !TRANSLATER_HPP_ */
