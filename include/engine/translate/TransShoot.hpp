//
// EPITECH PROJECT, 2018
// rtype
// File description:
// trans shoot
//

#ifndef TRANSSHOOT_HPP_
	#define TRANSSHOOT_HPP_

	#include "GameEngine.hpp"

namespace Engine {
	class TransShoot : public ITranslate {
	public:
		// Ctor & Dtor
		TransShoot(GameEngine &engine, std::istream &stream);
		TransShoot(unsigned int id, const Vector &target);
		~TransShoot() override = default;
		// Method
		void	apply() const override;
		void	serialize(std::ostream &) const noexcept override;
	private:
		GameEngine	*_engine;
		unsigned int	_id;
		const Vector	_target;
	};
}

#endif /* !TRANSSHOOT_HPP_ */
