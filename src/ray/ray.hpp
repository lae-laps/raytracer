#pragma once

#ifndef RAY_HPP
#define RAY_HPP

#include "../vec3/vec3.hpp"
#include "../objects/sphere/sphere.hpp"

class ray {
	public:

		point3 origin;
		vec3 direction;

		ray(const point3 &p, const vec3 &q);
		
		point3 at(val t) const;	
		color get_background_pixel() const;

		int hit_sphere(const sphere &s) const;							// returns number of intersects (roots) - 0, 1, 2


		color pixel_color() const;										// returns the color for each ray
};

#endif
