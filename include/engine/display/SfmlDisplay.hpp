/*
** EPITECH PROJECT, 2018
** Rtype
** File description:
** sfml class for the rtype
*/


#ifndef SFMLDISPLAY_HPP_
	#define SFMLDISPLAY_HPP_

	#include <SFML/Graphics.hpp>
	#include "IDisplay.hpp"
	#include "SfmlRenderer.hpp"

namespace Engine {
	class SfmlDisplay: public IDisplay {
	public:
		// Ctor & Dtor
		SfmlDisplay(std::string &path);
		~SfmlDisplay() override;
		// Operator
		// Setter
		// Getter
		// Method
		void	createWindow(unsigned int width,
			unsigned height, const std::string &name) noexcept;
		void	createWindow(bool fullscreen,
			const std::string &name) noexcept;
		ARenderer	*createRenderer(const std::string
					&ressourcesPath)
					const noexcept;
		ARenderer	*createRenderer(const std::string
					&ressourcesPath,
					const Rect &spriteRectangle)
					const noexcept;
		ARenderer	*createRenderer(const std::string
					&ressourcesPath,
					const Rect &spriteRectangle,
					const Vector &moveRect)	
					const noexcept;
		ARenderer	*createRenderer(const std::string
					&ressourcesPath,
					const Rect &spriteRectangle,
					const Vector &moveRect,
					const unsigned int maxRepetition)
					const noexcept;
		void		setFont();
		void		drawComponent(const IComponent &component);
		void		drawSceneScreen(ASceneScreen
				&sceneScreen);
		const InputKey	&getInputKey() const noexcept;
		const Vector	&getClickPos() const noexcept;
		bool		isWindowOpen() const noexcept;
		void		displayPause() const noexcept;
		void		displayMenu() const noexcept;
		void		displayBackground() const noexcept;
		void		playBackgroundMusic(std::string)
				const noexcept;
		void		eventHandler() noexcept;
		void		display() noexcept;
		void		drawBox(const Rect &box) noexcept;
		void		drawText(const std::string &text,
				const Vector &position, unsigned int size)
				noexcept;
		void		closeWindow() noexcept;
		void		drawRect(const Rect &rect, const Color &color)
				noexcept;
		void		drawCircle(const Vector &position,
				const Color &color, float radius)
				noexcept;
	private:
		void		createRenderState(
				const Transform &transform);
		void		setInputKey() noexcept;
		void		setClickPos() noexcept;
		void		scrollable(ASceneScreen &sceneSreen,
				SfmlRenderer *renderer) noexcept;
		InputKey		_inputKey = {false, 0, false};
		std::string		&_path;
		Vector		_clickPos = {0, 0};
		sf::RectangleShape	_rectangle;
		sf::RenderWindow	_window;
		sf::Event		_event;
		sf::RenderStates	_renderStates;
		sf::Font		_font;
		sf::Text		_sfText;
		Engine::Vector		_winSize;
	};
}
#endif /* !SFMLDISPLAY_HPP_ */
