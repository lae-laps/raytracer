#pragma once

#ifndef POINT_HPP
#define POINT_HPP

#include "../global.hpp"

class point {
	public:
		val x;
		val y;
		val z;

		point(val, val, val);

		void set_x(val);
		void set_y(val);
		void set_z(val);
};

#endif

