#pragma once

#ifndef RAY_HPP
#define RAY_HPP

#include "../vec3/vec3.hpp"

class ray {
	public:

		point3 origin;
		vec3 direction;

		ray() {}

		ray(const point3 &p, const vec3 &q);
		
		point3 at(val t) const;	
		color get_background_pixel() const;

};

#endif
