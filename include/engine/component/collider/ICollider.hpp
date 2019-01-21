//
// EPITECH PROJECT, 2018
// rtype
// File description:
// icollider
//

#ifndef ICOLLIDER_HPP_
	#define ICOLLIDER_HPP_

	#include "Vector.hpp"

namespace Engine {
	class ICollider {
	public:
		// Dtor
		virtual ~ICollider() = default;
		// Getter
		virtual const Vector	getEnd() const noexcept = 0;
		virtual const Vector	getOrigin() const noexcept = 0;
		// Method
		virtual bool	isColliding(const ICollider &collide)
							const noexcept = 0;
	};
}

#endif /* !ICOLLIDER_HPP_ */
