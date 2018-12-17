//
// EPITECH PROJECT, 2018
// rtype
// File description:
// ScriptedComponent
//

#ifndef SCRIPTEDCOMPONENT_HPP_
	#define SCRIPTEDCOMPONENT_HPP_

	#include "Component.hpp"
	#include "ScriptObject.hpp"

namespace Engine {
	class ScriptedComponent : public Component {
	public:
		// Ctor & Dtor
		ScriptedComponent(GameEngine &engine,
			bool friendly = false);
		ScriptedComponent(GameEngine &engine,
			const Transform &transform, bool friendly = false);
		ScriptedComponent(GameEngine &engine,
			std::vector<ScriptObject::Task> &tasks,
			bool friendly = false);
		ScriptedComponent(GameEngine &engine,
			const Transform &transform,
			std::vector<ScriptObject::Task> &tasks,
			bool friendly = false);
		virtual ~ScriptedComponent() override;
		// Operator
		// Setter
		// Getter
		ScriptObject	&getScript() noexcept;
		// Method
		void	doTick() override;
	private:
		ScriptObject	_script;
	};
}

#endif /* !SCRIPTEDCOMPONENT_HPP_ */
