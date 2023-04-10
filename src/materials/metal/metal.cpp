#include "metal.hpp"

bool metal::scatter(const ray &r_in, hit_record &rec, color &attenuation, ray &scattered) const {
	vec3 reflected = reflect(normalise(r_in.direction), rec.normal);

	// return the next ray (bounce) and multiply it by a random vector. This scatters the ray randomly
	// and it averages out over the image to generate a fuzziness which corresponds to fuzziness attribute
	// fuzziness = 0.0; -> 0 refraction (ideal mirror)

	scattered = ray(rec.p, reflected + fuzziness * random_unit_sphere());
	attenuation = albedo;
	return (dot(scattered.direction, rec.normal) > 0);
}

