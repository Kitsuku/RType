//
// EPITECH PROJECT, 2018
// rtype
// File description:
// component exception
//

#include "ComponentException.hpp"

using Engine::ComponentException;

ComponentException::ComponentException(const std::string &msg)
: EngineException(msg)
{
}
