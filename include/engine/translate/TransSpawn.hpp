//
// EPITECH PROJECT, 2018
// rtype
// File description:
// trans spawn
//

#ifndef TRANSSPAWN_HPP_
	#define TRANSSPAWN_HPP_

	#include "SceneLoader.hpp"

namespace Engine {
	class TransSpawn : public ITranslate {
	public:
		using AppActor = SceneApparition::SceneActor;
		// Ctor & Dtor
		TransSpawn(SceneLoader &loader, std::istream &stream);
		TransSpawn(unsigned int id, const AppActor &app);
		~TransSpawn() override = default;
		// Method
		void	apply() const override;
		void	serialize(std::ostream &) const noexcept override;
	private:
		SceneLoader	*_loader = nullptr;
		unsigned int	_id;
		AppActor	_apparition;
	};
}

#endif /* !TRANSSPAWN_HPP_ */
