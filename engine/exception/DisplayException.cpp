/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Exception method for display object
*/

#include "DisplayException.hpp"

using Engine::DisplayException;

DisplayException::DisplayException(const std::string &msg)
: EngineException(msg)
{
}