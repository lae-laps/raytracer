#pragma once

#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

#include "../global.hpp"
#include "../utils/utils.hpp"

#define ZERO_RANGE 1e-8

class vec3 {
	public:

		// Is it better to use 3 variables or an array?

		val x;
		val y;
		val z;

		vec3() : x(0), y(0), z(0) {}
		vec3(val, val, val);

		vec3  operator-() const;
		vec3& operator+=(const vec3 &v);
		vec3& operator-=(const vec3 &v);
		vec3& operator*=(const vec3 &v);
		vec3& operator/=(const vec3 &v);

		val length() const;
		val length_squared() const;

		bool near_zero() const;				// check if is in a range near to 0


		// Old declaration -> implicit cache poisoning

		inline static vec3 random() {
			return vec3(random_val(), random_val(), random_val());
		}

		inline static vec3 random(val min, val max) {
			return vec3(random_val(min, max), random_val(min, max), random_val(min, max));
		}

		/*inline static vec3 random(const val * &random_arr, unsigned int &random_arr_index) {
			random_arr_index += 3;
			return vec3(random_arr[random_arr_index + 1], random_arr[random_arr_index + 2], random_arr[random_arr_index + 3]);
		}

		inline static vec3 random(const val min, const val max, const val * &random_arr, unsigned int &random_arr_index) {
			return vec3(min + (max - min) * random_arr[random_arr_index + 1],
						min + (max - min) * random_arr[random_arr_index + 2],
						min + (max - min) * random_arr[random_arr_index + 3]);
		}*/
};

#endif

// aliases for vec3

using point3 = vec3;	// A 3-dimensional point
using color  = vec3;	// vectorial RGB color space

// vec3 utility functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
	return vec3(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
	return vec3(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
	return vec3(u.x * v.x, u.y * v.y, u.z * v.z);
}

inline vec3 operator*(const val t, const vec3 &u) {
	return vec3(t * u.x, t * u.y, t * u.z);
}

inline vec3 operator*(const vec3 &u, const val t) {
	return vec3(t * u.x, t * u.y, t * u.z);
}

inline vec3 operator/(const vec3 &u, const val t) {
	return static_cast<val>(1.0 / t) * u;
}

inline val dot(const vec3 &u, const vec3 &v) {
	return	u.x * v.x 
		  + u.y * v.y
		  + u.z * v.z;
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.y * v.z - u.z * v.y,
				u.z * v.x - u.x * v.z,
				u.x * v.y - u.y * v.x);
}

inline vec3 normalise(const vec3 v) {
	return v / v.length();
}

inline vec3 random_unit_sphere() {
    while (true) {
		vec3 p = vec3::random(-1,1);
		if (p.length_squared() >= 1) continue;
		return p;
	}
}

inline vec3 random_unit_vector() {
	return normalise(random_unit_sphere());
}

inline vec3 random_in_hemisphere(const vec3& normal) {
	vec3 in_unit_sphere = random_unit_sphere();
	if (dot(in_unit_sphere, normal) > 0.0) {
		// same hemisphere as the normal
		return in_unit_sphere;
	} else {
		// opposite hemisphere so we return the negative
		return -in_unit_sphere;
	}
}

inline vec3 reflect(const vec3 &v, const vec3 &normal) {
	return v - 2 * dot(v, normal) * normal;					// calculate reflected vector using snells law
}

