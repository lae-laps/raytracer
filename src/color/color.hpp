#pragma once

#ifndef COLOR_HPP
#define COLOR_HPP

#include "../vec3/vec3.hpp"

class color : public vec3 {
	public:
		void display() const;
};

#endif

