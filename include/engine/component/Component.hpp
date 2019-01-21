//
// EPITECH PROJECT, 2018
// rtype
// File description:
// component
//

#ifndef COMPONENT_HPP_
	#define COMPONENT_HPP_

	#include <ostream>
	#include "IComponent.hpp"
	#include "GameEngine.hpp"

namespace Engine {
	class Component : public IComponent {
	public:
		// Ctor & Dtor
		Component(GameEngine &engine, bool friendly);
		Component(GameEngine &engine, const Transform &transform,
					bool friendly);
		virtual ~Component() override;
		// Setter
		void	setID(int id) noexcept override;
		void	setObjective(bool state) noexcept;
		void	setBrain(IBrain *brain) noexcept override;
		void	setBullet(PreComponent *bullet) noexcept override;
		void	setCollider(ICollider *collider) noexcept override;
		void	setARenderer(ARenderer *renderer) noexcept override;
		// Getter
		bool		isObjective() const noexcept;
		bool		isFriendly() const noexcept override;
		int		getID() const noexcept override;
		Feature		&getFeature() noexcept override;
		Transform	&getTransform() noexcept override;
		const Feature	&getFeature() const noexcept override;
		const ICollider	*getCollider() const noexcept override;
		const Transform	&getTransform() const noexcept override;
		ARenderer	*getARenderer() const noexcept override;
		// Method
		virtual void	doTick() override;
		virtual void	onColliding(IComponent &compo) override;
		virtual void	shoot(const Vector &target,
					bool dir = true) const override;
	protected:
		GameEngine	&_engine;
		ARenderer	*_renderer = nullptr;
		ICollider	*_collider = nullptr;
		PreComponent	*_bullet = nullptr;
		bool		_objective = false;
		bool		_friendly = false;
		Feature		_feature;
		Transform	_transform;
		IBrain		*_brain = nullptr;
	private:
		int		_id;
		static int	next_id;
	};
}

	// Extern operator
	std::ostream	&operator<<(std::ostream &stream,
				const Engine::IComponent &target)
				noexcept;

#endif /* !ICOMPONENT_HPP_ */
