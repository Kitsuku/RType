//
// EPITECH PROJECT, 2018
// rtype
// File description:
// itask
//

#ifndef ITASK_HPP_
	#define ITASK_HPP_

	#include <ostream>

namespace Engine {
	class ITask;
}

	#include "IComponent.hpp"

namespace Engine {
	class ITask {
	public:
		virtual ~ITask() = default;
		// Method
		virtual bool	execute(IComponent &compo) noexcept = 0;
		virtual void	serialize(std::ostream &stream)
					const noexcept = 0;
	};
}

#endif /* !ITASK_HPP_ */
