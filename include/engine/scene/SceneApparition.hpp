//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scene actor and apparition
//

#ifndef SCENEAPPARITION_HPP_
	#define SCENEAPPARITION_HPP_

	#include "Transform.hpp"
	#include "ScriptObject.hpp"

namespace Engine {
	struct SceneApparition {
	public:
		struct SceneActor {
		public:
			// Attributs
			unsigned int	actor = 0;
			bool		team = false;
			Transform	transform;
			bool		objective = false;
		};
		// Attribut
		double		delta = 0;
		SceneActor	actor;
		ScriptObject	*script = nullptr;
		bool		end = false;
	};
}

#endif /* !SCENEAPPARITION_HPP_ */
