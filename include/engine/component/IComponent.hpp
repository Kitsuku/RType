//
// EPITECH PROJECT, 2018
// rtype
// File description:
// icomponent
//

#ifndef ICOMPONENT_HPP_
	#define ICOMPONENT_HPP_

namespace Engine {
	class IComponent;
}

	#include <ostream>
	#include "IBrain.hpp"
	#include "Transform.hpp"
	#include "ARenderer.hpp"
	#include "PreComponent.hpp"
	#include "Feature.hpp"
	#include "ICollider.hpp"

namespace Engine {
	class IComponent {
	public:
		// Ctor & Dtor
		virtual ~IComponent() = default;
		// Setter
		virtual void	setID(int id) noexcept = 0;
		virtual void	setBrain(IBrain *brain) noexcept = 0;
		virtual void	setObjective(bool state) noexcept = 0;
		virtual void	setBullet(PreComponent *bullet) noexcept = 0;
		virtual void	setCollider(ICollider *collider) noexcept = 0;
		virtual void	setARenderer(ARenderer *renderer)
							noexcept = 0;
		// Getter
		virtual bool		isFriendly() const noexcept = 0;
		virtual bool		isObjective() const noexcept = 0;
		virtual int		getID() const noexcept = 0;
		virtual Feature		&getFeature() noexcept = 0;
		virtual Transform	&getTransform() noexcept = 0;
		virtual const Feature	&getFeature() const noexcept = 0;
		virtual	const ICollider	*getCollider() const noexcept = 0;
		virtual const Transform	&getTransform() const noexcept = 0;
		virtual ARenderer	*getARenderer() const noexcept = 0;
		// Method
		virtual void	doTick() = 0;
		virtual void	onColliding(IComponent &compo) = 0;
		virtual void	shoot(const Vector &target,
						bool dir = true) const = 0;
	};
}

	// Extern operator
	std::ostream	&operator<<(std::ostream &stream,
				const Engine::IComponent &target)
				noexcept;

#endif /* !ICOMPONENT_HPP_ */
