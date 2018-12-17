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
		return (ret);
	}
}
