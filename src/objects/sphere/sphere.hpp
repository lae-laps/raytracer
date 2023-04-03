#pragma once

#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../../vec3/vec3.hpp"
#include "../hittable/hittable.hpp"

#include <memory>
#include <vector>

class sphere : public hittable {
	public:
		point3 center;
		val radius;
		shared_ptr<material> mat_ptr;

		sphere() {}													// default constructor
		//sphere(point3 b, val a, material n);						// data constructor
		sphere(point3 cen, double r, shared_ptr<material> m): center(cen), radius(r), mat_ptr(m) {};
																	
		bool hit(const ray &r, const val t_min, const val t_max, hit_record &rec) const;

};

#endif

