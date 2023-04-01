#include "ray.hpp"
#include "../math/math.hpp"
#include "../vec3/vec3.hpp"
#include "../objects/sphere/sphere.hpp"

#include <cmath>

ray::ray(const point3 &p, const vec3 &q) {
	origin = p;
	direction = q;
}

color ray::get_background_pixel() const {
	vec3 unit_direction = normalise(direction);
	val t = 0.5 * (unit_direction.y + 1.0);
	// blendedValue=(1−t)⋅startValue+t⋅endValue, with t going from 0 to 1
	// start is start value (color) and end finish value(color)
	return (1.0 - t) * color(GRADIENT_BACKGROUND_START[0], GRADIENT_BACKGROUND_START[1], GRADIENT_BACKGROUND_START[2]) + t * color(GRADIENT_BACKGROUND_END[0], GRADIENT_BACKGROUND_END[1], GRADIENT_BACKGROUND_END[2]);
}

point3 ray::at(const val t) const {
	return origin + direction * t;
}

