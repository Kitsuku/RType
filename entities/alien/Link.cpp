//
// EPITECH PROJECT, 2018
// rtype
// File description:
// link alien
//

#include <iostream>
#include "PreComponent.hpp"

using Engine::PreComponent;

extern "C" {
	PreComponent	build() {
		PreComponent	ret;

		ret.brain = nullptr;
		ret.path = "r-typesheet9.gif";
		ret.rectangle.pos_x = 52;
		ret.rectangle.pos_y = 0;
		ret.rectangle.width = 60;
		ret.rectangle.height = 58;
		ret.bullet = new PreComponent;
		ret.bullet->brain = nullptr;
		ret.bullet->path = "r-typesheet9.gif";
		ret.bullet->rectangle.pos_x = 35;
		ret.bullet->rectangle.pos_y = 58;
		ret.bullet->rectangle.width = 65;
		ret.bullet->rectangle.height = 18;
		return (ret);
	}
}
