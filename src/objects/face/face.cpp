#include <cmath>

#include "face.hpp"
#include "../../io/io.hpp"

face::face(point3 *points) {

	if (std::extent<decltype(points)>::value < 3) {
		throw_error("face must have at least 3 vertices");
	}

	// check if the points are collinear

	vec3 ab(points[1] - points[0]);
	vec3 ac(points[2] - points[1]);

	vec3 check = cross(ab, ac);

	if (check.x == 0 and check.y == 0 and check.z == 0) {
		throw_error("points for declaration of face are collinear");
	}

	vertices = points;

	plane[0] = points[0];
	plane[1] = points[1];
	plane[2] = points[2];

	normal = cross(ab, ac);

}

bool face::hit(const ray &r, const val t_min, const val t_max, hit_record &rec) const {
	
}

