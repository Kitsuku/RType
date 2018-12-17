/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** abstract for scene screen displaying screen in the game
*/

#ifndef ASCENESCREEN_HPP_
	#define ASCENESCREEN_HPP_

namespace Engine {
	class Button;
}

	#include <vector>
	#include "Vector.hpp"
	#include "ARenderer.hpp"
	#include "Button.hpp"
	#include "ButtonRequest.hpp"
	#include "Transform.hpp"

namespace Engine {
	class ASceneScreen {
	public:
		// CTOR && DTOR
		ASceneScreen(const Transform &transform,
		const bool scrollable = false);
		ASceneScreen(ARenderer *renderer,
		const Transform &transform, const bool scrollable = false);
		~ASceneScreen();
		// Getter
		ARenderer		*getARenderer() const noexcept;
		bool			isScrollable() const noexcept;
		const ButtonRequest	&getRequest() const noexcept;
		Transform		&getTransform() noexcept;
		const Transform		&getTransform() const noexcept;
		const Vector		&getInitialPos() const noexcept;
		const std::vector<Button>	&getButtons() const noexcept;
		// Setter
		void		setARenderer(ARenderer *renderer)
				noexcept;
		void		setScrollabe(const bool scrollable)
				noexcept;
		void		setButtonPos(int buttonPos) noexcept;
		void		setButtons(std::vector<Button> buttons) noexcept;
		void		setInitialPos(Vector _initialPos) noexcept;
		// Method
		bool		isPressed(const Vector &clickPos)
				noexcept;
		const ASceneScreen	&operator=(const ASceneScreen
					&sceneScreen) noexcept;
	protected:
		ARenderer		*_renderer = nullptr;
		Transform		_transform;
		bool			_scrollable;
		std::vector<Button>	_buttons;
		int			_buttonPos = 0;
		Vector			_initialPos;
	private:
		virtual void	initButtons() noexcept = 0;
	};
}
#endif /* !ASCENESCREEN_HPP_ */