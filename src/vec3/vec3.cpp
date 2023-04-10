#include "vec3.hpp"
#include "../utils/utils.hpp"

#include <cmath>

vec3::vec3(val a, val b, val c) {		// constructor

	x = a;
	y = b;
	z = c;

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
	//return std::sqrt(length_squared());	-> This works but implies an extra function call
	
	return std::sqrt(x * x + y * y + z * z);

}

val vec3::length_squared() const {
	return x * x + y * y + z * z;
}

bool vec3::near_zero() const {
	return (std::fabs(x) < ZERO_RANGE) && (std::fabs(y) < ZERO_RANGE) && (std::fabs(z) < ZERO_RANGE);
}


