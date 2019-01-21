//
// EPITECH PROJECT, 2018
// rtype
// File description:
// collider static
//

#ifndef COLLIDERSTATIC_HPP_
	#define COLLIDERSTATIC_HPP_

	#include "ICollider.hpp"

namespace Engine {
	class ColliderStatic : public ICollider {
	public:
		// Ctor & Dtor
		ColliderStatic(const Vector &start, const Vector &size);
		~ColliderStatic() override = default;
		// Getter
		const Vector	getEnd() const noexcept override;
		const Vector	getOrigin() const noexcept override;
		// Method
		bool	isColliding(const ICollider &collide)
						const noexcept override;
	private:
		Vector	_origin;
		Vector	_end;
	};
}

#endif /* !COLLIDERSTATIC_HPP_ */
