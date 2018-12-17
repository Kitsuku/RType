//
// EPITECH PROJECT, 2018
// rtype
// File description:
// engine exception
//

#include "EngineException.hpp"

using Engine::EngineException;

EngineException::EngineException(const std::string &msg)
: _msg(msg)
{
}

// Method
const char	*EngineException::what() const noexcept
{
	return _msg.c_str();
}