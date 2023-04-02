#pragma once

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../hit.hpp"
#include "../../vec3/vec3.hpp"
#include "../hittable/hittable.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;

class sphere : public hittable {
	public:
		val radius;
		point3 center;

		sphere() : radius(1.0), center(point3(0.0, 0.0, 0.0)) {}	// default constructor
		sphere(point3 b, val a, material n);						// data constructor
																	
		virtual bool hit(const ray &r, const val t_min, const val t_max, class hit rec, shared_ptr<material>) const override;

};

#endif

