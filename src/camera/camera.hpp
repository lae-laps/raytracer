#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "../ray/ray.hpp"
#include "../vec3/vec3.hpp"

/*	A camera object is initialized with an origin vector, a destination or lookat vector which sets direction
 *	and lastly some data which sets the fov. This can either be a number which is equivalent to the focal length 
 *	or a set of vertical fov (vertical angle the camera is looking at(in degrees)) and an aspect ratio
 */

class Camera {
	public:
		Camera();													// initialize to (0, 0, 0) by default
		Camera(const point3, const point3, const vec3, const val, const val, const bool, const val);
		Camera(const point3, const point3, const vec3, const val, const val, const bool, const val, const val);				// initialize to focal length
																													
		// Camera(origin, direction, rotation, focal_distance, aspect_ratio, use_defocus_blur, focus_distance, aperture);

		//Camera(const point3, const point3, const val, const val);	// initialize to vertical angle and aspect ratio

		ray get_ray(const val u, const val v) const;
	
	private:
		point3 origin;
		point3 lower_left_corner;
		vec3 horizontal;
		vec3 vertical;
		vec3 u, v, w;
		//val aspect_ratio;
		//val focal_length;
		bool defocus_blur;
		//val focus_distance;
		val lens_radius;
};

#endif

