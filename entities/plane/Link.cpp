//
// EPITECH PROJECT, 2018
// rtype
// File description:
// link plane
//

#include "PreComponent.hpp"

using Engine::PreComponent;

extern "C" {
	PreComponent	build() {
		PreComponent	ret;

		ret.brain = nullptr;
		ret.path = "r-typesheet5.gif";
		ret.rectangle.pos_x = 0;
		ret.rectangle.pos_y = 0;
		ret.rectangle.width = 33;
		ret.rectangle.height = 36;
		ret.bullet = new PreComponent;
		ret.bullet->brain = nullptr;
		ret.bullet->path = "r-typesheet43.gif";
		ret.bullet->rectangle.pos_x = 136;
		ret.bullet->rectangle.pos_y = 6;
		ret.bullet->rectangle.width = 7;
		ret.bullet->rectangle.height = 6;
		return (ret);
	}
}
