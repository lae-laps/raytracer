#include "dielectric.hpp"

bool dielectric::scatter(const ray& r, hit_record& rec, color &attenuation, ray& scattered) const {

	attenuation = albedo;

	val refraction_ratio = rec.front_face ? (AIR_REFRACTIVE_INDEX / ri) : ri;

	vec3 unit_direction = normalise(r.direction);

	val a = dot(-unit_direction, rec.normal);

	//val cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);	-> fmin forces double -> to make it portable calculate directly min

	val cos_theta = (a > 1.0) ? 1.0 : a;

	val sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	vec3 direction;

	// check if eta / eta' is bigger than 1
	// if it is, it means total internal reflection is happening, so the ray does not refract, it just reflects
	// we also set the option to arbitrarilly relect under a random probability. This is much more economic than the 
	// actual analytical solution to reflectance but the error is almost neglible for most purposes

	if (refraction_ratio * sin_theta > 1.0 || reflectance(cos_theta, refraction_ratio) > random_val()) {
		direction = reflect(unit_direction, rec.normal);
	} else {
		direction = refract(unit_direction, rec.normal, refraction_ratio, cos_theta);
	}

	scattered = ray(rec.p, direction);
	return true;

}

val dielectric::reflectance(const val cosine, const val ref_index) {

	// Use Christophe Schlick approximation to reflectance

	auto r0 = (1 - ref_index) / (1 + ref_index);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

