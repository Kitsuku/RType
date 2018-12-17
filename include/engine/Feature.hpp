//
// EPITECH PROJECT, 2018
// rtype
// File description:
// feature
//

#ifndef FEATURE_HPP_
	#define FEATURE_HPP_

namespace Engine {
	class Feature {
	public:
		// Ctor & Dtor
		Feature(unsigned int life = 1, unsigned int damages = 1);
		~Feature() = default;
		// Setter
		void	setSpeed(float speed) noexcept;
		void	setDamageable(bool state) noexcept;
		void	setDamages(unsigned int damages) noexcept;
		// Getter
		bool		isAlive() const noexcept;
		bool		isDeletable() const noexcept;
		float		getSpeed() const noexcept;
		unsigned int	getDamages() const noexcept;
		// Method
		void	kill() noexcept;
		void	resurect() noexcept;
		void	heal(unsigned int value) noexcept;
		void	damage(unsigned int value) noexcept;
	private:
		unsigned int	_maxLife;
		unsigned int	_life;
		unsigned int	_damages;
		float	_speed = 1.0;
		bool	_alive = true;
		bool	_isDeletable = true;
		bool	_isDamageable = true;
	};
}

#endif /* !FEATURE_HPP_ */
