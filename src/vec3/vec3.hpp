#pragma once

#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

#include "../global.hpp"

#define ZERO_RANGE 1e-8

class vec3 {
	public:

		// Is it better to use 3 variables or an array?

		val x;
		val y;
		val z;

		vec3(val, val, val);

		vec3  operator-() const;
		vec3& operator+=(const vec3 &v);
		vec3& operator-=(const vec3 &v);
		vec3& operator*=(const vec3 &v);
		vec3& operator/=(const vec3 &v);

		val length() const;
		val length_squared() const;

		bool near_zero() const;				// check if is in a range near to 0

		inline static vec3 random();
		inline static vec3 random(val, val);

	protected:
		static val random_val();
		static val random_val(val, val);

};

#endif

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
	return t * u;
}

inline vec3 operator/(const vec3 &u, const val t) {
	return (1 / t) * u;
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

inline vec3 unit_vec(const vec3 v) {
	return v / v.length();
}

