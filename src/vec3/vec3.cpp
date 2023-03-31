#include "vec3.hpp"

#include <cmath>

vec3::vec3(val a, val b, val c) {		// constructor

	x = a;
	y = b;
	z = c;

}

val vec3::random_val() {
	return (val)rand() / RAND_MAX;
}

val vec3::random_val(const val min, const val max) {
	val f = (val)rand() / RAND_MAX;
	return min + f * (max - min);
}

vec3 vec3::operator-() const {
	return vec3(-x, -y, -z);
}

vec3& vec3::operator+=(const vec3 &v) {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

vec3& vec3::operator-=(const vec3 &v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

vec3& vec3::operator*=(const vec3 &v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

vec3& vec3::operator/=(const vec3 &v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

val vec3::length() const {
	return std::sqrt(length_squared());
}

val vec3::length_squared() const {
	return x * x + y * y + z * z;
}

bool vec3::near_zero() const {
	return (std::fabs(x) < ZERO_RANGE) && (std::fabs(y) < ZERO_RANGE) && (std::fabs(z) < ZERO_RANGE);
}

inline vec3 vec3::random() {
	return vec3(random_val(), random_val(), random_val());
}

inline vec3 vec3::random(val min, val max) {
	return vec3(random_val(min, max), random_val(min, max), random_val(min, max));
}


