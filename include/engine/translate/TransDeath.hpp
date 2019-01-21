//
// EPITECH PROJECT, 2018
// rtype
// File description:
// trans death
//

#ifndef TRANSDEATH_HPP_
	#define TRANSDEATH_HPP_

	#include "GameEngine.hpp"

namespace Engine {
	class TransDeath : public ITranslate {
	public:
		// Ctor & Dtor
		TransDeath(GameEngine &engine, std::istream &stream);
		TransDeath(unsigned int id);
		~TransDeath() override = default;
		// Method
		void	apply() const override;
		void	serialize(std::ostream &) const noexcept override;
	private:
		GameEngine	*_engine = nullptr;
		unsigned int	_id;
	};
}

#endif /* !TRANSDEATH_HPP_ */
