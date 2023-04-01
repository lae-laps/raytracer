#pragma once

#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "../../global.hpp"
#include "../../ray/ray.hpp"
#include "../../vec3/vec3.hpp"

struct hit_record {
	point3 p;
	vec3 normal;
	val t;
	bool front_face;
	

	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
	    front_face = dot(r.direction, outward_normal) < 0;
	    normal = front_face ? outward_normal :-outward_normal;
	}
};

class hittable {
	public:
		
		hittable() {}
		~hittable() {}

		virtual bool hit(const ray &r, const val t_min, const val t_max, hit_record &rec) const = 0;		// = 0; avoids vtable redefinition errors -> https://stackoverflow.com/questions/3065154/undefined-reference-to-vtable
};

#endif

