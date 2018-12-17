/*
** EPITECH PROJECT, 2018
** R-type
** File description:
** Sfml renderer header heriting from ARenderer
*/

#ifndef SFMLRENDERER_HPP_
	#define SFMLRENDERER_HPP_

	#include <SFML/Graphics.hpp>
	#include "Vector.hpp"
	#include "ARenderer.hpp"

namespace Engine {
	class SfmlRenderer: public ARenderer {
	public:
		// Ctor & Dtor
		SfmlRenderer(const std::string &path);
		SfmlRenderer(const std::string &path,
			const Rect &spriteRectangle);
		SfmlRenderer(const std::string &path,
			const Rect &spriteRectangle,
			const Engine::Vector &moveRect);
		SfmlRenderer(const std::string &path,
			const Rect &spriteRectangle,
			const Engine::Vector &moveRect,
			const unsigned int maxRepetition);
		~SfmlRenderer() override = default;
		// Getter
		const sf::Texture	&getTexture() const noexcept;
		const sf::Sprite	&getSprite() const noexcept;
		// Setter
		void		setTexturePath(const std::string
				&path) noexcept;
		void		setSpriteRect(const Rect
				&spriteRectangle) noexcept;
		// Method
		void		setSpritePosition(const Engine::Vector
				&position) noexcept;
		void		setSpriteRotation(const Engine::Vector
				&rotation) noexcept;
		void		setSpriteScale(const Engine::Vector
				&scale) noexcept;
		void		moveRectSprite() noexcept;
	private:
		void		updateOpacity() noexcept;
		sf::Texture	_texture;
		sf::Sprite	_sprite;
	};
}

#endif /* !SFMLRENDERER_HPP_ */
