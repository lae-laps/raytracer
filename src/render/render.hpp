#pragma once

#ifndef RENDER_HPP
#define RENDER_HPP

#include "../ray/ray.hpp"
#include "../math/math.hpp"
#include "../objects/hittable/hittable.hpp"

color render_color(const ray &r, const hittable &world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1,1,1));
	}
	return r.get_background_pixel();
}

#endif

