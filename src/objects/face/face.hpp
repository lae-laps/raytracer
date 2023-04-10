#pragma once

#ifndef FACE_HPP
#define FACE_HPP

#include "../../vec3/vec3.hpp"
#include "../hittable/hittable.hpp"

class face : public hittable {
	public:
		point3 plane[3];
		point3 *vertices;

		vec3 normal;

		face(point3 *p);

		bool hit(const ray &r, const val t_min, const val t_max, hit_record &rec) const;

};

#endif

