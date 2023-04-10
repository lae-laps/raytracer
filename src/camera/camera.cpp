#include "camera.hpp"
#include "../math/math.hpp"

Camera::Camera() {
	val viewport_height = 2.0;
	val viewport_width = aspect_ratio * viewport_height;
	val focal_length = 1.0;

	origin = point3(0, 0, 0);
	horizontal = vec3(viewport_width, 0.0, 0.0);
	vertical = vec3(0.0, viewport_height, 0.0);
	lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
}

Camera::Camera(const point3 o, const vec3 direction, const vec3 rotation, const val focal, const val ar, const bool blur, const val aperture) {

	val focus_distance = (o - direction).length();

	val vfov = (1 / focal) * 90;
	val theta = degrees_to_radians(vfov);
	val h = tan(theta / 2);

	val viewport_height = 2.0 * h;
	val viewport_width = ar * viewport_height;

	w = normalise(o - direction);
	u = normalise(cross(rotation, w));
	v = cross(w, u);

	origin = o;
	//focal_length = focal;
	//aspect_ratio = ar;

	if (blur) {
		horizontal = viewport_width * u * focus_distance;
		vertical = viewport_height * v * focus_distance;
		lower_left_corner = origin - horizontal/2 - vertical/2 - focus_distance*w;
	} else {
		horizontal = viewport_width * u;
		vertical = viewport_height * v;
		lower_left_corner = origin - horizontal/2 - vertical/2 - w;
	}



	defocus_blur = blur;
	lens_radius = aperture / 2;

}

Camera::Camera(const point3 o, const vec3 direction, const vec3 rotation, const val focal, const val ar, const bool blur, const val aperture, const val foc_dist) {

	val vfov = (1 / focal) * 90;
	val theta = degrees_to_radians(vfov);
	val h = tan(theta / 2);

	val viewport_height = 2.0 * h;
	val viewport_width = ar * viewport_height;

	w = normalise(o - direction);
	u = normalise(cross(rotation, w));
	v = cross(w, u);

	origin = o;
	//focal_length = focal;
	//aspect_ratio = ar;

	horizontal = viewport_width * u;
	vertical = viewport_height * v;

	if (blur) {
		horizontal = horizontal * foc_dist;
		vertical = vertical * foc_dist;

		lower_left_corner = origin - horizontal/2 - vertical/2 - w * foc_dist;
	} else {
		lower_left_corner = origin - horizontal/2 - vertical/2 - w;
	}

	defocus_blur = blur;
	//focus_distance = foc_dist;
	lens_radius = aperture / 2;

}

/*Camera::Camera(const point3 o, const point3 direction, const val vfov, const val aspect_ratio) {

	origin = o;

	val theta = degrees_to_radians(vfov);
	val h = tan(theta/2);
	val viewport_height = 2.0 * h;
	val viewport_width = aspect_ratio * viewport_height;


	val focal_length = 1.0;

	horizontal = vec3(viewport_width, 0.0, 0.0);
	vertical = vec3(0.0, viewport_height, 0.0);
	lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

}*/

ray Camera::get_ray(const val s, const val t) const {
	if (!defocus_blur) {
		return ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);			// calculate ray trajectory
	} else {
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x + v * rd.y;

		return ray(
			origin + offset,
			lower_left_corner + s * horizontal + t * vertical - origin - offset
		);
	}
}

