//
// EPITECH PROJECT, 2018
// rtype
// File description:
// actor loader
//

#ifndef ACTORLOADER_HPP_
	#define ACTORLOADER_HPP_

	#include <string>
	#include <vector>

	#include "PreComponent.hpp"

namespace Engine {
	class ActorLoader {
	public:
		// Ctor & Dtor
		ActorLoader();
		~ActorLoader();
		// Operator
		PreComponent	operator[](unsigned int idx) const;
		// Method
		void	reset() noexcept;
		void	addActor(const std::string &path);
	private:
		using ptr = PreComponent (*)();
		// Private method
		void	stackActor(void *handle);
		// Attributs
		std::vector<ptr>	_actors;
		std::vector<void*>	_handlers;
	};
}

#endif /* !ACTORLOADER_HPP_ */
