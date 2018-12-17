//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task shoot
//

#ifndef TASKSHOOT_HPP_
	#define TASKSHOOT_HPP_

	#include "ITask.hpp"

namespace Engine {
	class TaskShoot : public ITask {
	public:
		// Ctor & Dtor
		TaskShoot(std::ifstream &stream);
		TaskShoot(const Vector &objective);
		~TaskShoot() override = default;
		// Method
		bool	execute(IComponent &compo) noexcept override;
		void	serialize(std::ostream &s) const noexcept override;
	private:
		Vector	_target;
	};
}

#endif /* !TASKSHOOT_HPP_ */
