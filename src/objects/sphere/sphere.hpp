#pragma once

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../../vec3/vec3.hpp"
#include "../hittable/hittable.hpp"

class sphere : public hittable {
	public:
		val radius;
		point3 center;

		sphere() : radius(1.0), center(point3(0.0, 0.0, 0.0)) {}	// default constructor
		sphere(point3 b, val a) : radius(a), center(b) {}			// data constructor
																	
		bool hit(const ray &r, const val t_min, const val t_max, hit_record &rec) const;

};

#endif

