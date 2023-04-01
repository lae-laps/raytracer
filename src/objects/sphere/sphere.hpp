#pragma once

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../../vec3/vec3.hpp"

class sphere {
	public:
		val radius;
		point3 center;

		sphere() : radius(1.0), center(point3(0.0, 0.0, 0.0)) {}	// default constructor
		sphere(val a, point3 b) : radius(a), center(b) {}			// data constructor

};

#endif

