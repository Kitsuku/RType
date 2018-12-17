//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scene exception
//

#ifndef SCENEEXCEPTION_HPP_
	#define SCENEEXCEPTION_HPP_

	#include "EngineException.hpp"

namespace Engine {
	class SceneException : public EngineException {
	public:
		// Ctor & Dtor
		SceneException(const std::string &msg);
		~SceneException() override = default;
	};
}

#endif /* !SCENEEXCEPTION_HPP_ */
