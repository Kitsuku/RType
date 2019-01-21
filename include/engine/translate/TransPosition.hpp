//
// EPITECH PROJECT, 2018
// rtype
// File description:
// trans position
//

#ifndef TRANSPOSITION_HPP_
	#define TRANSPOSITION_HPP_

	#include "GameEngine.hpp"

namespace Engine {
	class TransPosition : public ITranslate {
	public:
		// Ctor & Dtor
		TransPosition(GameEngine &engine, std::istream &stream);
		TransPosition(int id, const Vector &position);
		~TransPosition() override = default;
		// Method
		void	apply() const override;
		void	serialize(std::ostream &stream) const
							noexcept override;
	private:
		GameEngine	*_engine = nullptr;
		int		_id;
		const Vector	_position;
	};
}

#endif /* !TRANSPOSITION_HPP_ */
