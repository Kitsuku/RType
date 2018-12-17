//
// EPITECH PROJECT, 2018
// rtype
// File description:
// scene exception
//

#include "SceneException.hpp"

using Engine::SceneException;

SceneException::SceneException(const std::string &msg)
: EngineException(msg)
{
}