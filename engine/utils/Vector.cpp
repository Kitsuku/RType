//
// EPITECH PROJECT, 2018
// rtype
// File description:
// vector
//

#include "Vector.hpp"

using Engine::Vector;

// Ctor & Dtor
Vector::Vector(std::istream &stream)
{
	stream.read(reinterpret_cast<char*>(&_x), sizeof(_x));
	stream.read(reinterpret_cast<char*>(&_y), sizeof(_y));
}

Vector::Vector(float x, float y) : _x(x), _y(y)
{
}

Vector::~Vector()
{
}

// Operator
const Vector    &Vector::operator+=(const Vector &other) noexcept
{
        _x += other.getX();
        _y += other.getY();
        return *this;
}

const Vector    &Vector::operator*=(float coef) noexcept
{
        _x *= coef;
        _y *= coef;
        return *this;
}

const Vector    &Vector::operator=(const Vector &other) noexcept
{
        _x = other.getX();
        _y = other.getY();
        return *this;
}

bool            Vector::operator==(const Vector &other) const noexcept
{
        return (other.getX() == _x && other.getY() == _y);
}

bool            Vector::operator!=(const Vector &other) const noexcept
{
        return !(*this == other);
}

// Setter
void    Vector::setX(float x) noexcept
{
        _x = x;
}

void    Vector::setY(float y) noexcept
{
        _y = y;
}

void    Vector::setNull() noexcept
{
        _x = 0.0;
        _y = 0.0;
}

// Getter
bool    Vector::isNull() const noexcept
{
        return (_x == 0.0 && _y == 0.0);
}

float   Vector::getX() const noexcept
{
        return _x;
}

float   Vector::getY() const noexcept
{
        return _y;
}

// Method
void    Vector::serialize(std::ostream &stream) const noexcept
{
	stream.write(reinterpret_cast<const char*>(&_x), sizeof(_x));
	stream.write(reinterpret_cast<const char*>(&_y), sizeof(_y));
}

// Extern operator
std::ostream      &operator<<(std::ostream &stream,
                                const Vector &target) noexcept
{
        stream << target.getX() << ";" << target.getY();
        return stream;
}