#include "lambertian.hpp"

bool lambertian::scatter(const ray& r_in, hit_record &rec, color &attenuation, ray &scattered) const {

	vec3 scatter_direction = rec.normal + random_unit_vector();

	if (scatter_direction.near_zero()) {
	
		// scatter direction could be opposite to normal which would lead to problems
		// if it is opposite, or very near to being opposite, we just return the normal

		scatter_direction = rec.normal;
	}

	scattered = ray(rec.p, scatter_direction);
	attenuation = albedo;
	return true;
}

