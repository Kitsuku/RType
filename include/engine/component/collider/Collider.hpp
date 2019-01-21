//
// EPITECH PROJECT, 2018
// rtype
// File description:
// collider
//

#ifndef COLLIDER_HPP_
	#define COLLIDER_HPP_

	#include "IComponent.hpp"

namespace Engine {
	class Collider : public ICollider {
	public:
		// Ctor & Dtor
		Collider(const IComponent &compo, const Rect &rect);
		Collider(const IComponent &compo, unsigned int width,
						unsigned int height);
		~Collider() override = default;
		// Getter
		const Vector	getEnd() const noexcept override;
		const Vector	getOrigin() const noexcept override;
		// Method
		bool	isColliding(const ICollider &collide)
						const noexcept override;
		// Static method
		static Collider	*wrapRenderer(const IComponent &target);
	protected:
		const IComponent	&_component;
		Vector			_size;
	};
}

#endif /* !COLLIDER_HPP_ */
