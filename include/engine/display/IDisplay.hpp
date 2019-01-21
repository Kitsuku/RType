/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** interface for graphical lib
*/

#ifndef IDISPLAY_HPP_
	#define IDISPLAY_HPP_

namespace Engine {
	class IDisplay;
}

namespace Engine {
	class ASceneScreen;
}

	#include <string>
	#include "InputKey.hpp"
	#include "ARenderer.hpp"
	#include "Rect.hpp"
	#include "IComponent.hpp"
	#include "Vector.hpp"
	#include "ASceneScreen.hpp"
	#include "Color.hpp"

namespace Engine {
	class IDisplay {
	public:
		// Ctor & Dtor
		virtual ~IDisplay() = default;
		// Operator
		// Setter
		// Getter
		// Method
		virtual void	createWindow(unsigned int width,
				unsigned height,const std::string &name)
				noexcept = 0;
		virtual void	createWindow(bool fullscreen,
				const std::string &name) noexcept = 0;
		virtual ARenderer	*createRenderer(
					const std::string
					&ressourcesPath)
					const noexcept = 0;
		virtual ARenderer	*createRenderer(
					const std::string
					&ressourcesPath,
					const Rect
					&spriteRectangle)
					const noexcept = 0;
		virtual ARenderer	*createRenderer(
					const std::string
					&ressourcesPath,
					const Rect
					&spriteRectangle,
					const Vector &moveRect)
					const noexcept = 0;
		virtual ARenderer	*createRenderer(
					const std::string
					&ressourcesPath,
					const Rect
					&spriteRectangle,
					const Vector &moveRect,
					const unsigned int maxRepetition)
					const noexcept = 0;
		virtual void		setFont() = 0;
		virtual void	drawComponent(const IComponent
				&component) = 0;
		virtual void	drawSceneScreen(ASceneScreen
				&aSceneScreen) = 0;
		virtual void	drawBox(const Rect &box) noexcept = 0;
		virtual void	drawText(const std::string &text,
				const Vector &position, unsigned int size)
				noexcept = 0;
		virtual void	drawRect(const Rect &rect, const Color &color)
				noexcept = 0;
		virtual void	drawCircle(const Vector &position,
				const Color &color, float radius)
				noexcept = 0;
		virtual	const InputKey		&getInputKey() const noexcept = 0;
		virtual	const Vector	&getClickPos()
						const noexcept = 0;
		virtual bool	isWindowOpen() const noexcept = 0;
		virtual void	displayPause() const noexcept = 0;
		virtual void	displayMenu() const noexcept = 0;
		virtual void 	displayBackground() const noexcept = 0;
		virtual void	playBackgroundMusic(std::string)
				const noexcept = 0;
		virtual void	eventHandler() noexcept = 0;
		virtual void	display() noexcept = 0;
		virtual void	closeWindow() noexcept = 0;
	};
}
#endif /* !IDISPLAY_HPP_ */
