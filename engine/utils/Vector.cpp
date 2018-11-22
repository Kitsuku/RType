//
// EPITECH PROJECT, 2018
// rtype
// File description:
// vector
//

#include "Vector.hpp"

using Engine::Vector;

// Ctor & Dtor
Vector::Vector(float x, float y)
{
}

Vector::~Vector()
{
}

// Operator
const Vector &Vector::operator+=(const Vector &other) noexcept
{
        _x += other.getX();
        _y += other.getY();
		return *this;
}

const Vector &Vector::operator=(const Vector &other) noexcept
{
        _x = other.getX();
        _y = other.getY();
		return other;
}

// Setter
void Vector::setX(float x) noexcept
{
        _x = x;
}

void Vector::setY(float y) noexcept
{
        _y = y;
}

// Getter
float Vector::getX() const noexcept
{
        return _x;
}

float Vector::getY() const noexcept
{
        return _y;
}
