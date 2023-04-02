#pragma once

#ifndef RENDER_HPP
#define RENDER_HPP

#include <cmath>

#include "../ray/ray.hpp"
#include "../math/math.hpp"
#include "../objects/hit.hpp"
#include "../utils/utils.hpp"
#include "../objects/hittable/hittable.hpp"

#include "../materials/metal/metal.hpp"
#include "../materials/material/material.hpp"
#include "../materials/lambertian/lambertian.hpp"

inline color render_color(const ray &r, const hittable &world, const unsigned int iterations, mat_struct &m) {
    hit rec;

	if (iterations <= 0) {
		return color(0, 0, 0);
	}

	//material m;

    if (world.hit(r, shadow_acne_threshold, infinity, rec, m)) {

		//return 0.5 * (rec.normal + color(1,1,1));						// convert surface normal to RGB value
		//point3 target = rec.p + rec.normal + random_unit_vector();	// non-exac
		//point3 target = rec.p + random_in_hemisphere(rec.normal);		// real lambertian noise
		//return 0.5 * render_color(ray(rec.p, target - rec.p), world, iterations - 1);

		ray scattered;
		color attenuation;

		if (m.c.scatter(r, rec, attenuation, scattered)) {
			return attenuation * render_color(scattered, world, iterations - 1, m);
		}

		return color(0,0,0);

	}
	return r.get_background_pixel();
}

inline color even_color(const color s) {

	// even out added light over cycles

	val scale = 1.0 / samples_per_pixel;

	val r = s.x;
	val g = s.y;
	val b = s.z;

	r *= scale;
	g *= scale;
	b *= scale;

	// lazy approach to gamma correction

	// use gamma = 2.0

	const val n = 2.0;

	r = std::pow(r, 1.0 / n);
	g = std::pow(g, 1.0 / n);
	b = std::pow(b, 1.0 / n);

	return color(snap(r), snap(g), snap(b));

}

#endif

