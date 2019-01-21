//
// EPITECH PROJECT, 2018
// rtype
// File description:
// task direction
//

#ifndef TASKDIRECTION_HPP_
	#define TASKDIRECTION_HPP_

	#include "ITask.hpp"

namespace Engine {
	class TaskDirection : public ITask {
	public:
		// Ctor & Dtor
		TaskDirection(std::ifstream &stream);
		TaskDirection(float x, float y, float maxDist = -1);
		TaskDirection(const Vector &direction);
		~TaskDirection() override = default;
		// Method
		bool	execute(IComponent &compo)
						noexcept override;
		void	serialize(std::ostream &stream)
						const noexcept override;
	private:
		// Private method
		void	calcAttributs(float x, float y);
		// Attribut
		Vector	_percent;
		float	_maxDist;
	};
}

#endif /* !TASKDIRECTION_HPP_ */
