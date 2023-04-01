#include "collection.hpp"
#include "../../io/io.hpp"

Collection::Collection() {
	sphere_count = 0;
	spheres = new sphere[max_spheres]();			// () initializes to zeros
}

void Collection::add_sphere(sphere s) {
	
	if (sphere_count + 1 > max_spheres) {
		throw_error("too many spheres");
	}

	spheres[sphere_count] = s;
	sphere_count++;
}

