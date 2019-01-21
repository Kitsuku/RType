//
// EPITECH PROJECT, 2018
// rtype
// File description:
// i translate
//

#ifndef ITRANSLATE_HPP_
	#define ITRANSLATE_HPP_

namespace Engine {
	class ITranslate {
	public:
		// Dtor
		virtual ~ITranslate() = default;
		// Method
		virtual void	apply() const = 0;
		virtual void	serialize(std::ostream &stream)
							const noexcept = 0;
	};
}

#endif /* !ITRANSLATE_HPP_ */
