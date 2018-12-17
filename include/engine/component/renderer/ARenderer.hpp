//
// EPITECH PROJECT, 2018
// rtype
// File description:
// arenderer
//

#ifndef ARENDERER_HPP_
	#define ARENDERER_HPP_

	#include <string>
	#include "Vector.hpp"
	#include "Rect.hpp"

namespace Engine {
	class ARenderer {
	public:
		// Ctor & Dtor
		ARenderer(const std::string &texturePath,
		const Rect &spriteRectangle = {0, 0, 17, 50},
		const Vector &moveRect = Vector(0, 0),
		const unsigned int maxRepetition = 1);
		virtual ~ARenderer() = default;
		// Getter
		bool	isVisible() const noexcept;
		float	getOpacity() const noexcept;
		bool	isHighLight() const noexcept;
		const std::string	&getTexturePath() const noexcept;
		const Rect	&getSpriteRectangle() const noexcept;
		const Vector	&getVectorMove() const noexcept;
		unsigned int	getMaxRepetition() const noexcept;
		// Setter
		void		setOpacity(float opacity) noexcept;
		void		setHighLight(bool highLight) noexcept;
		virtual void	setTexturePath(const std::string
					&path) noexcept = 0;
		virtual void	setSpriteRect(const Rect
				&spriteRectangle) noexcept = 0;
		void		setVectorMove(const Vector &vectorMove)
				noexcept;
		void		setMaxRepetition(const unsigned int
				maxRepetition) noexcept;
		// Method
		void	show() noexcept;
		void	hide() noexcept;
	protected:
		virtual void	updateOpacity() noexcept = 0;
		bool	_visible = true;
		float	_opacity = 255.0;
		bool	_highLighted = false;
		unsigned int	_beginRepetition = 0;
		std::string	_texturePath;
		Rect	_spriteRectangle;
		Vector	_vectorMove;
		unsigned int	_maxRepetition;
	};
}

#endif /* !ARENDERER_HPP_ */
