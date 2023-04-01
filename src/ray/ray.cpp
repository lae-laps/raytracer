#include "ray.hpp"
#include "../vec3/vec3.hpp"
#include "../global_collection.hpp"
#include "../objects/sphere/sphere.hpp"

ray::ray(const point3 &p, const vec3 &q) {
	origin = p;
	direction = q;
}

color ray::get_background_pixel() const {
	vec3 unit_direction = unit_vec(direction);
	val t = 0.5 * (unit_direction.y + 1.0);
	// blendedValue=(1−t)⋅startValue+t⋅endValue, with t going from 0 to 1
	// start is start value (color) and end finish value(color)
	return (1.0 - t) * color(GRADIENT_BACKGROUND_START[0], GRADIENT_BACKGROUND_START[1], GRADIENT_BACKGROUND_START[2]) + t * color(GRADIENT_BACKGROUND_END[0], GRADIENT_BACKGROUND_END[1], GRADIENT_BACKGROUND_END[2]);
}

int ray::hit_sphere(const sphere &s) const {
	vec3 oc = origin - s.center;
	val a = dot(direction, direction);
	val b = 2.0 * dot(oc, direction);
	val c = dot(oc, oc) - s.radius * s.radius;
	val discriminant = b * b - 4 * a * c;
	if (discriminant > 0) {
		return 2;
	} else if (discriminant == 0) {
		return 1;
	} else {
		return 0;
	}
}

color ray::pixel_color() const {
	for (unsigned int i = 0; i < collection.sphere_count; i++) {
		int hits = hit_sphere(collection.spheres[i]);
		if (hits) {
			return color(1, 0, 0);
		}
	}

	return get_background_pixel();
}

